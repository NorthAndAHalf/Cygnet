#include "Traceable.h"
#include "RayHit.h"
#include "glm/gtc/random.hpp"

Traceable::Traceable()
    : primitives(new std::vector<Primitive*>)
{
}

Traceable::~Traceable()
{
    delete primitives;
}

RayHit Traceable::Trace(Ray& ray, std::vector<Traceable*>& traceables, uint8_t depth, uint8_t limit) // Recursion depth is temporary until russian roulette is implemented
{
    // The acceleration structure for each traceable will be traced in this function
    std::vector<RayHit> hits;
    for (Primitive* p : *primitives)
    {
        RayHit h = p->Trace(ray, depth);
        hits.push_back(h); 
    }

    // Implement rendering equation here
    // Returned light = emittedLight + Integrate(reflection * reflectedLight * cosTheta)
    
    // Probably need to rethink the RayHit class
    // Rayhits should store the material, get returned from the primitive trace function, then the rendering equation evaluated here I guess
    // Ray AABB hits should still work if the origin is inside the traceable's box but I guess we'll find out

    RayHit* output;
    output = &hits.front();

    for (RayHit h : hits)
    {
        if (hits.size() !=0) 
            if(h.t < output->t && h.t >= 0.0f) output = &h;
    }

    int samples = 16;

    glm::vec3 integratedLight = glm::vec3(0.0f);
    std::vector<Traceable*> intersected = std::vector<Traceable*>();

    for (int i = 0; i < samples; i++)
    {
        float theta = glm::radians(glm::linearRand(0.0f, 90.0f));
        float phi = glm::radians(glm::linearRand(0.0f, 90.0f));

        glm::vec3 unitDir = glm::vec3(glm::cos(phi) * glm::cos(theta), glm::sin(theta), glm::sin(phi) * glm::cos(theta));
        // Next, use this unit dir to transform a vector from the normal

    }

    return *output;
}

float Traceable::Intersect(Ray& ray)
{
    // Temporary Implementation: This will be replaced with an intersection test of the bounding volume once they are implemented
    float t = -1.0f;
    for (Primitive* p : *primitives)
    {
        float pt = p->Intersect(ray);
        if (t < 0.0f && pt >= 0.0f) t = pt;
        else if (t > 0.0f && pt < t && pt >= 0.0f) t = pt;
    }
    return t;
}

void Traceable::AddPrimitive(Primitive* p)
{
    primitives->push_back(p);
}

void IntersectTraceables(Ray& ray, const std::vector<Traceable*>& traceables, std::vector<Traceable*>& output)
{
    for (Traceable* t : traceables)
    {
        float tt = t->Intersect(ray);
        if (tt >= 0.0f) output.push_back(t);
    }
}
