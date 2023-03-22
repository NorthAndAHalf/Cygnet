#include "Application.h"
#include "spdlog/spdlog.h"
#include "Traceable/Sphere.h"
#include "Traceable/Triangle.h"
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
	std::vector<Traceable*>* traceables = new std::vector<Traceable*>();
	Sphere* sphere = new Sphere(glm::vec3(1.0f, 0.0f, -2.0f), 0.3f);
	Triangle* triangle = new Triangle(glm::vec3(-0.5f, -0.5f, -2.0f), glm::vec3(0.0f, 0.5f, -2.0f), glm::vec3(0.5f, -0.5f, -2.0f));	
	Traceable model = Traceable();
	model.AddPrimitive(triangle);
	model.AddPrimitive(sphere);
	traceables->push_back(&model);

	uint8_t* pixels = new uint8_t[width * height * 3];

	// Temporary loop to trace 1 perspective ray per pixel:
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			//idk why but all the uint8_ts in the pixel array have a default value of 205
			pixels[((x + (y * width)) * 3)] = 0;
			pixels[((x + (y * width)) * 3) + 1] = 0;
			pixels[((x + (y * width)) * 3) + 2] = 0;
			glm::vec3 pixelCoord = glm::vec3(2 * (double)x / (double)width - 1, 2 * (double)y / (double)height - 1, -focalLength);
			Ray ray = Ray(glm::vec3(0.0f), glm::normalize(pixelCoord));
			std::vector<Traceable*> intersected = std::vector<Traceable*>();

			RayHit* hit;
			IntersectTraceables(ray, *traceables, intersected);

			// Next step, traverse the acceleration structure of each intsersected traceable

			if (!intersected.empty()) hit = &intersected.at(0)->Trace(ray, *traceables, 0);
			else hit = nullptr;

			glm::vec3 colour;
			if (hit != nullptr) colour = hit->mat.albedo;
			else colour = glm::vec3(0.0f);
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
