#include "Application.h"
#include "spdlog/spdlog.h"
#include "Trace.h"
#include "Traceable/Sphere.h"
#include "Traceable/Triangle.h"
#include "Traceable/Traceable.h"
#include "Ray.h"
#include "glm/geometric.hpp"
#include "BRDF/BRDF.h"

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

	spdlog::info("Starting");

	const int width = 500;
	const int height = 500;
	float focalLength = 1.7f;

	// I want to use smart pointers instead of these raw pointers everywhere
	// But idk how tf that works with inheritance
	std::vector<Traceable*>* traceables = new std::vector<Traceable*>();
	/*Sphere* sphere = new Sphere(glm::vec3(0.5f, 0.0f, -1.5f), 0.3f);
	Triangle* triangle = new Triangle(glm::vec3(-0.5f, -0.5f, -2.0f), glm::vec3(-0.5f, 0.5f, -2.0f), glm::vec3(0.5f,  0.5f, -2.0f));
	Triangle* triangle2 = new Triangle(glm::vec3(0.5f, 0.5f, -2.0f), glm::vec3(0.5f, -0.5f, -2.0f), glm::vec3(-0.5f, -0.5f, -2.0f));
	Traceable model = Traceable();
	model.AddPrimitive(sphere);
	Traceable model2 = Traceable();
	model2.AddPrimitive(triangle);
	model2.AddPrimitive(triangle2);
	model.ApplyMaterial(Material(glm::vec3(1.0f), 30.0f));
	model2.ApplyMaterial(Material(glm::vec3(1.0f, 0.0f, 0.0f), 0.0f));
	traceables->push_back(&model);
	traceables->push_back(&model2);*/

	// BTEC Cornell Box

	glm::vec3 centre = glm::vec3(0.0f, 0.0f, -2.0f);

	glm::vec3 v1 = centre + glm::vec3(-1.0f, -1.0f,  1.0f);
	glm::vec3 v2 = centre + glm::vec3(-1.0f,  1.0f,  1.0f);
	glm::vec3 v3 = centre + glm::vec3(-1.0f,  1.0f, -1.0f);
	glm::vec3 v4 = centre + glm::vec3(-1.0f, -1.0f, -1.0f);

	glm::vec3 v5 = centre + glm::vec3( 1.0f, -1.0f,  1.0f);
	glm::vec3 v6 = centre + glm::vec3( 1.0f,  1.0f,  1.0f);
	glm::vec3 v7 = centre + glm::vec3( 1.0f,  1.0f, -1.0f);
	glm::vec3 v8 = centre + glm::vec3( 1.0f, -1.0f, -1.0f);

	// Floor
	Triangle* floor1 = new Triangle(v1, v4, v8);
	Triangle* floor2 = new Triangle(v8, v5, v1);
	Traceable floor = Traceable();
	floor.AddPrimitive(floor1);
	floor.AddPrimitive(floor2);
	floor.ApplyMaterial(Material(glm::vec3(1.0f), 0.0f, DiffuseBRDF()));
	traceables->push_back(&floor);

	// Left Wall
	Triangle* wallL1 = new Triangle(v1, v2, v3);
	Triangle* wallL2 = new Triangle(v3, v4, v1);
	Traceable leftWall = Traceable();
	leftWall.AddPrimitive(wallL1);
	leftWall.AddPrimitive(wallL2);
	leftWall.ApplyMaterial(Material(glm::vec3(1.0f, 0.0f, 0.0f), 0.0f, DiffuseBRDF()));
	traceables->push_back(&leftWall);

	// Right Wall
	Triangle* wallR1 = new Triangle(v7, v6, v5);
	Triangle* wallR2 = new Triangle(v5, v8, v7);
	Traceable rightWall = Traceable();
	rightWall.AddPrimitive(wallR1);
	rightWall.AddPrimitive(wallR2);
	rightWall.ApplyMaterial(Material(glm::vec3(0.0f, 1.0f, 0.0f), 0.0f, DiffuseBRDF()));
	traceables->push_back(&rightWall);

	// Back Wall
	Triangle* wallB1 = new Triangle(v4, v3, v7);
	Triangle* wallB2 = new Triangle(v7, v8, v4);
	Traceable backWall = Traceable();
	backWall.AddPrimitive(wallB1);
	backWall.AddPrimitive(wallB2);
	backWall.ApplyMaterial(Material(glm::vec3(1.0f), 0.0f, DiffuseBRDF()));
	traceables->push_back(&backWall);

	// Front Wall
	Triangle* wallF1 = new Triangle(v6, v2, v1);
	Triangle* wallF2 = new Triangle(v1, v5, v6);
	Traceable frontWall = Traceable();
	frontWall.AddPrimitive(wallF1);
	frontWall.AddPrimitive(wallF2);
	frontWall.ApplyMaterial(Material(glm::vec3(1.0f), 0.0f, DiffuseBRDF()));
	frontWall.ignoreFirst = true;
	traceables->push_back(&frontWall);

	// Ceiling
	Triangle* ceil1 = new Triangle(v7, v3, v2);
	Triangle* ceil2 = new Triangle(v2, v6, v7);
	Traceable ceiling = Traceable();
	ceiling.AddPrimitive(ceil1);
	ceiling.AddPrimitive(ceil2);
	ceiling.ApplyMaterial(Material(glm::vec3(1.0f), 0.0f, DiffuseBRDF()));
	traceables->push_back(&ceiling);

	// Light
	Triangle* light1 = new Triangle(v2 + glm::vec3(0.75f, -0.01f, -0.75f), v2 + glm::vec3(0.75f, -0.01f, -1.25f), v2 + glm::vec3(1.25f, -0.01f, -1.25f));
	Triangle* light2 = new Triangle(v2 + glm::vec3(1.25f, -0.01f, -1.25f), v2 + glm::vec3(1.25f, -0.01f, -0.75f), v2 + glm::vec3(0.75f, -0.01f, -0.75f));
	Traceable light = Traceable();
	light.AddPrimitive(light1);
	light.AddPrimitive(light2);
	light.ApplyMaterial(Material(glm::vec3(1.0f), 25.0f, DiffuseBRDF()));
	traceables->push_back(&light);

	// Sphere
	Sphere* sphere = new Sphere(centre, 0.4f);
	Traceable sphereObj = Traceable();
	sphereObj.AddPrimitive(sphere);
	sphereObj.ApplyMaterial(Material(glm::vec3(1.0f), 0.0f, DiffuseBRDF()));
	traceables->push_back(&sphereObj);

	uint8_t* pixels = new uint8_t[width * height * 3];

	spdlog::info("Rendering " + std::to_string(traceables->size()) + " traceables");
	// Temporary loop to trace 1 perspective ray per pixel:
	for (int y = 0; y < height; y++)
	{
		// Percentage counter
		if((int)(((float)y/(float)height)*1000.0f)%100 == 0) spdlog::info(std::to_string((int)(((float)y / (float)height) * 100)) + "%");
		for (int x = 0; x < width; x++)
		{
			//idk why but all the uint8_ts in the pixel array have a default value of 205
			pixels[((x + (y * width)) * 3)] = 0;
			pixels[((x + (y * width)) * 3) + 1] = 0;
			pixels[((x + (y * width)) * 3) + 2] = 0;
			glm::vec3 pixelCoord = glm::vec3(2 * (double)x / (double)width - 1, 2 * (double)y / (double)height - 1, -focalLength);
			Ray ray = Ray(glm::vec3(0.0f), glm::normalize(pixelCoord));
			std::vector<Traceable*> intersected = std::vector<Traceable*>();

			RayHit hit = IntersectTraceablesIgnoreFirst(ray, *traceables);

			glm::vec3 colour = Trace(hit, *traceables, 0, 2);
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
