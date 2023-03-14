#include "Application.h"
#include "spdlog/spdlog.h"
#include "Traceable/Sphere.h"
#include "Traceable/Traceable.h"
#include "Ray.h"
#include "glm/geometric.hpp"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#ifdef _DEBUG
#define SPD_DEBUG_LEVEL(x) x;
#else
#define SPD_DEBUG_LEVEL(x);
#endif

Application::Application() {}

void Application::Run()
{
	// Setting up spdlog level, spdlog::trace() will only print when in debug configuration, other log functions will work in all configurations
	SPD_DEBUG_LEVEL(spdlog::set_level(spdlog::level::trace));
	std::string path = "render.bmp";

	const int width = 1000;
	const int height = 1000;
	float focalLength = 1.0f;

	// I want to use smart pointers instead of these raw pointers everywhere
	// But idk how tf that works with inheritance
	Sphere* sphere = new Sphere(glm::vec3(0.0f, 0.0f, -2.0f), 0.5f);
	Traceable model = Traceable();
	model.AddPrimitive(sphere);

	uint8_t* pixels = new uint8_t[width * height * 3];

	// Temporary loop to trace 1 perspective ray per pixel:
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			glm::vec3 pixelCoord = glm::vec3(2 * (double)x / (double)width - 1, 2 * (double)y / (double)height - 1, -focalLength);
			Ray ray = Ray(glm::vec3(0.0f), glm::normalize(pixelCoord));

			// Will need to trace multiple models here
			// Maybe a function that takes in an array of traceables, intersects them all, and returns a pointer to the one with
			// the closest intersection
			// Intersect function could sample the acceleration structure, then Trace() traces the primitives directly using the return t value?
			// idk yet, might need to be restructured
			// 
			// Maybe store a list of pointer primitives?
			// Or more likely make another hit point class but this time have them only able to store actual geometry hits

			glm::vec3 colour = model.Trace(ray);
			pixels[((x + (y * width)) * 3)]		= colour.x * 255;
			pixels[((x + (y * width)) * 3) + 1] = colour.y * 255;
			pixels[((x + (y * width)) * 3) + 2] = colour.z * 255;
		}
	}

	stbi_write_bmp(path.data(), width, height, 3, pixels);
	spdlog::info("Finished");

	// Opening image file:
	system(path.data());
}
