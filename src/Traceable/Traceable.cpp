#include "Traceable.h"

Traceable::Traceable()
    : primitives(new std::vector<Primitive*>)
{
}

Traceable::~Traceable()
{
    delete primitives;
}

glm::vec3 Traceable::Trace(Ray& ray)
{
    glm::vec3 tempOut;
    for (Primitive* p : *primitives)
    {
        tempOut = p->Trace(ray);
    }
    return tempOut;
}

float Traceable::Intersect(Ray& ray)
{
    // TODO: Return t value of closest intersection
    for (Primitive* p : *primitives)
    {
        p->Trace(ray);
    }
    return -1.0f;
}

float Traceable::Intersect(Ray& ray, glm::vec3& colour)
{
    // TODO: Return t value of closest intersection and output the colour of the intersection colour at the intersecion point
    for (Primitive* p : *primitives)
    {
        p->Trace(ray);
    }

    colour = glm::vec3(0.0f);
    return -1.0f;
}

void Traceable::AddPrimitive(Primitive* p)
{
    primitives->push_back(p);
}
