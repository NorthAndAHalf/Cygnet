#include "Traceable.h"

glm::vec3 Traceable::Trace(Ray& ray)
{
    // TODO: Combine trace results for all objects into one colour
    for (std::shared_ptr<Primitive> p : *primitives.get())
    {
        p->Trace(ray);
    }
    return glm::vec3();
}

float Traceable::Intersect(Ray& ray)
{
    // TODO: Return t value of closest intersection
    for (std::shared_ptr<Primitive> p : *primitives.get())
    {
        p->Trace(ray);
    }
    return -1.0f;
}

float Traceable::Intersect(Ray& ray, glm::vec3& colour)
{
    // TODO: Return t value of closest intersection and output the colour of the intersection colour at the intersecion point
    for (std::shared_ptr<Primitive> p : *primitives.get())
    {
        p->Trace(ray);
    }

    colour = glm::vec3(0.0f);
    return -1.0f;
}
