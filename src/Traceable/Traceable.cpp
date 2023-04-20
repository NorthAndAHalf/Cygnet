#include "Traceable.h"
#include "RayHit.h"
#include "glm/gtc/random.hpp"
#include "glm/gtx/transform.hpp"
#include "glm/gtx/rotate_vector.hpp"
#include "Triangle.h"

Traceable::Traceable()
    : primitives(new std::vector<Primitive*>), hasBVH(false)
{
}

Traceable::~Traceable()
{
    for (Primitive* p : *primitives)
        delete p;

    delete primitives;
}

void Traceable::ConstructBVH()
{
    bvh = std::make_unique<BVH>(primitives, 8);
    hasBVH = true;
}

RayHit Traceable::Intersect(const Ray& ray)
{
    if (hasBVH)
    {
        Triangle::intersectionCount = 0;
        std::vector<RayHit> hits;
        bool isIntersected = bvh->Intersect(ray, &hits);

        RayHit closest = RayHit();
        if (isIntersected)
        {
            for (const RayHit& h : hits)
            {
                if (h.miss)
                    continue;
                if (closest.miss)
                {
                    closest = h;
                    continue;
                }
                if (h.t < closest.t && h.t > 0.0001f)
                {
                    closest = h;
                }
            }
        }
        return closest;
    }

    std::pair<Primitive*, float> closest = std::pair<Primitive*, float>(nullptr, -1.0f);
    bool miss = true;

    for (Primitive* p : *primitives)
    {
        float t = p->IntersectTest(ray);

        if (t == -1.0f)
        {
            continue;
        }

        if (closest.first == nullptr)
        {
            closest.first = p;
            closest.second = t;
            miss = t == -1.0f;
            continue;
        }

        if (closest.second > t && t > 0.0001f)
        {
            closest.first = p;
            closest.second = t;
        }
    }

    if (miss)
    {
        return RayHit();
    }

    return closest.first->Intersect(ray);
}

void Traceable::AddModel(const Model& model)
{
    const std::vector<glm::vec3>& vertices = model.GetVertices();
    const std::vector<unsigned int>& indices = model.GetIndices();

    for (int p = 0; p < indices.size() - 3; p+=3)
    {
        glm::vec4 i1 = glm::vec4(vertices.at(indices.at(p)), 1.0f);
        glm::vec4 i2 = glm::vec4(vertices.at(indices.at(p + 1)), 1.0f);
        glm::vec4 i3 = glm::vec4(vertices.at(indices.at(p + 2)), 1.0f);

        i1 = glm::rotateX(i1, model.rot.x);
        i1 = glm::rotateY(i1, model.rot.y);
        i1 = glm::rotateZ(i1, model.rot.z);

        i2 = glm::rotateX(i2, model.rot.x);
        i2 = glm::rotateY(i2, model.rot.y);
        i2 = glm::rotateZ(i2, model.rot.z);

        i3 = glm::rotateX(i3, model.rot.x);
        i3 = glm::rotateY(i3, model.rot.y);
        i3 = glm::rotateZ(i3, model.rot.z);
        
        i1 *= glm::vec4(model.scale, model.scale, model.scale, 1.0f);
        i2 *= glm::vec4(model.scale, model.scale, model.scale, 1.0f);
        i3 *= glm::vec4(model.scale, model.scale, model.scale, 1.0f);

        glm::vec3 i1v3 = glm::vec3(i1.x, i1.y, i1.z);
        glm::vec3 i2v3 = glm::vec3(i2.x, i2.y, i2.z);
        glm::vec3 i3v3 = glm::vec3(i3.x, i3.y, i3.z);

        i1v3 += model.pos;
        i2v3 += model.pos;
        i3v3 += model.pos;

        // This pointer is deleted in the traceable's destructor
        Triangle* triangle = new Triangle(i1v3, i2v3, i3v3);
        primitives->push_back(triangle);
    }
}

void Traceable::AddPrimitive(Primitive* p)
{
    primitives->push_back(p);
}

void Traceable::ApplyMaterial(Material* mat)
{
    for (Primitive* p: *primitives)
    {
        p->ApplyMaterial(mat);
    }
}

unsigned int Traceable::NumberOfPrimitives()
{
    return primitives->size();
}

