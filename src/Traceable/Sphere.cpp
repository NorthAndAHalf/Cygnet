#include "Sphere.h"
#include "glm/geometric.hpp"

Sphere::Sphere(glm::vec3 _centre, float _radius)
    : centre(_centre), radius(_radius)
{
}

// Surface colour should be multipled by the luminance of all reflected rays
// So if all reflected rays return (0,0,0), the result will be pure black
// The lack of multi importance sampling here will likely produce a very noisy image
// Am I going to start with distributed ray tracing immedatiately?
// Probably since this lighting approach won't really work with Whitted raytracing
// I guess to get the final luminance at a ray hit point, we could combine the reflected rays' contributions with a multi importance sampling
// Light contribution, then multiply that by the surface colour?
// Don't forget to use the ray equation to calculate the luminance at a point
// AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA

glm::vec3 Sphere::Trace(Ray& ray)
{
    glm::vec3 surfaceContribution;
    float t = Intersect(ray, surfaceContribution);
    //spdlog::trace(t);
    if (t < 0.0f) return glm::vec3(0.0f);

    // Step 1: Recursively reflect rays by sampling the BRDF (I guess MIS will be implemented here)
    // Step 2: Combine all colours reflected rays colours into one reflection contribution
    // Step 3: Combine surfaceContribution with reflection contribution
    // Step 4: Return final colour

    glm::vec3 reflectedContribution = glm::vec3(0.8f); // Temporary, just so I can get a sphere rendering atm

    // idk how the colours are combined atm. Here I'm giving them equal weighting but I don't know
    // how it is done in the rendering equation
    glm::vec3 output = (surfaceContribution * reflectedContribution);
    return output;
}

float Sphere::Intersect(Ray& ray)
{
    glm::vec3 oc = ray.origin - centre; 
    float b = glm::dot(oc, ray.direction);
    float c = dot(oc, oc) - radius * radius;
    float h = (b * b) - c; //spdlog::trace(c);
    if (h < 0.0f) return -1.0f;
    h = sqrt(h);
    float t = -b - h;
    return t;
}

float Sphere::Intersect(Ray& ray, glm::vec3& colour)
{
    float t = Intersect(ray);
    // Sample colour from texture or something from ray.At(t) idk, just a hardcoded colour for now
    colour = glm::vec3(1.0f, 0.0f, 0.0f);
    return t;
}
