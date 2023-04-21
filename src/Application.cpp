#include "Application.h"
#include "spdlog/spdlog.h"
#include "Trace.h"
#include "Traceable/Sphere.h"
#include "Traceable/Triangle.h"
#include "Traceable/Traceable.h"
#include "Ray.h"
#include "glm/geometric.hpp"
#include "BRDF/BRDF.h"
#include "glm/gtc/random.hpp"
#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"
#include "glm/gtc/constants.hpp"
#include "Models/Model.h"

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

	std::vector<Traceable*>* traceables = new std::vector<Traceable*>();

	Assimp::Importer importer;

	const aiScene* pScene = importer.ReadFile("C:/Users/lewis/Downloads/stanford_dragon_pbr.glb", aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_JoinIdenticalVertices);

	if (!pScene)
	{
		spdlog::critical(importer.GetErrorString());
		return;
	}

	Model model = Model(pScene, glm::vec3(0.0f, -0.5f, -2.5f), glm::vec3(0.0f, 3.14f, 0.0f), 0.01f);
	//model.Print();

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

	BRDF* brdf = &BRDF();

	// Floor
	Triangle* floor1 = new Triangle(v1, v4, v8);
	Triangle* floor2 = new Triangle(v8, v5, v1);
	Traceable floor = Traceable();
	floor.AddPrimitive(floor1);
	floor.AddPrimitive(floor2);
	Material floorMat = Material(glm::vec3(1.0f), 0.0f, brdf);
	floor.ApplyMaterial(&floorMat);
	traceables->push_back(&floor);

	// Left Wall
	Triangle* wallL1 = new Triangle(v1, v2, v3);
	Triangle* wallL2 = new Triangle(v3, v4, v1);
	Traceable leftWall = Traceable();
	leftWall.AddPrimitive(wallL1);
	leftWall.AddPrimitive(wallL2);
	Material wallLMat = Material(glm::vec3(0.0f, 1.0f, 0.0f), 0.0f, brdf);
	leftWall.ApplyMaterial(&wallLMat);
	traceables->push_back(&leftWall);

	// Right Wall
	Triangle* wallR1 = new Triangle(v7, v6, v5);
	Triangle* wallR2 = new Triangle(v5, v8, v7);
	Traceable rightWall = Traceable();
	rightWall.AddPrimitive(wallR1);
	rightWall.AddPrimitive(wallR2);
	Material wallRMat = Material(glm::vec3(1.0f, 0.0f, 0.0f), 0.0f, brdf);
	rightWall.ApplyMaterial(&wallRMat);
	traceables->push_back(&rightWall);

	// Back Wall
	Triangle* wallB1 = new Triangle(v4, v3, v7);
	Triangle* wallB2 = new Triangle(v7, v8, v4);
	Traceable backWall = Traceable();
	backWall.AddPrimitive(wallB1);
	backWall.AddPrimitive(wallB2);
	Material wallBMat = Material(glm::vec3(1.0f), 0.0f, brdf);
	backWall.ApplyMaterial(&wallBMat);
	traceables->push_back(&backWall);

	// Front Wall
	Triangle* wallF1 = new Triangle(v6, v2, v1);
	Triangle* wallF2 = new Triangle(v1, v5, v6);
	Traceable frontWall = Traceable();
	frontWall.AddPrimitive(wallF1);
	frontWall.AddPrimitive(wallF2);
	Material wallFMat = Material(glm::vec3(1.0f), 0.0f, brdf);
	frontWall.ApplyMaterial(&wallFMat);
	frontWall.ignoreFirst = true;
	traceables->push_back(&frontWall);

	// Ceiling
	Triangle* ceil1 = new Triangle(v7, v3, v2);
	Triangle* ceil2 = new Triangle(v2, v6, v7);
	Traceable ceiling = Traceable();
	ceiling.AddPrimitive(ceil1);
	ceiling.AddPrimitive(ceil2);
	Material ceilMat = Material(glm::vec3(1.0f), 0.0f, brdf);
	ceiling.ApplyMaterial(&ceilMat);
	traceables->push_back(&ceiling);

	// Light
	Triangle* light1 = new Triangle(v2 + glm::vec3(0.75f, -0.001f, -0.75f), v2 + glm::vec3(0.75f, -0.001f, -1.25f), v2 + glm::vec3(1.25f, -0.001f, -1.25f));
	Triangle* light2 = new Triangle(v2 + glm::vec3(1.25f, -0.001f, -1.25f), v2 + glm::vec3(1.25f, -0.001f, -0.75f), v2 + glm::vec3(0.75f, -0.001f, -0.75f));
	Traceable light = Traceable();
	light.AddPrimitive(light1);
	light.AddPrimitive(light2);
	Material lightMat = Material(glm::vec3(1.0f), 30.0f, brdf);
	light.ApplyMaterial(&lightMat);
	traceables->push_back(&light);

	// Sphere
	/*Sphere* sphere = new Sphere(centre, 0.4f);
	Traceable sphereObj = Traceable();
	sphereObj.AddPrimitive(sphere);
	Material sphereMat = Material(glm::vec3(1.0f), 0.0f, brdf);
	sphereObj.ApplyMaterial(&sphereMat);
	traceables->push_back(&sphereObj);*/

	// Creeper Aw mam
	Traceable creeper = Traceable();
	creeper.AddModel(model);
	Material sphereMat = Material(glm::vec3(1.0f), 0.0f, brdf);
	creeper.ApplyMaterial(&sphereMat);
	creeper.ConstructBVH();
	traceables->push_back(&creeper);

	Scene* scene = new Scene(traceables);

	uint8_t* pixels = new uint8_t[width * height * 3];
	uint8_t samples = 48; // 1D samples, so the actual sample count will be squared

	// Only works for square images atm
	// Currently extrememley scuffed btw, I think it works though?
	float pixelDistance = glm::vec3(2 * (double)1 / (double)width - 1, 2 * (double)1 / (double)height - 1, -focalLength).x - glm::vec3(2 * (double)0 / (double)width - 1, 2 * (double)0 / (double)height - 1, -focalLength).x;
	float sampleDistance = pixelDistance / samples;
	
	spdlog::info("Rendering " + std::to_string(traceables->size()) + " traceables");
	// Temporary loop to trace 1 perspective ray per pixel:
	for (int y = height - 1; y >= 0; y--)
	{
		// Percentage counter
		if((int)(((float)y/(float)height)*1000.0f)%100 == 0) spdlog::info(std::to_string(100 - (int)(((float)y / (float)height) * 100)) + "%");
		for (int x = 0; x < width; x++)
		{
			//idk why but all the uint8_ts in the pixel array have a default value of 205
			pixels[((x + (y * width)) * 3)] = 0;
			pixels[((x + (y * width)) * 3) + 1] = 0;
			pixels[((x + (y * width)) * 3) + 2] = 0;
			
			glm::vec3 radiance = glm::vec3(0.0f);
			glm::vec3 pixelCoord = glm::vec3(2 * (double)x / (double)width - 1, 2 * (double)y / (double)height - 1, -focalLength);

			for (int i = 0; i < samples; i++)
			{
				for (int j = 0; j < samples; j++)
				{
					glm::vec3 s = glm::vec3(pixelCoord.x + (sampleDistance * j), pixelCoord.y + (sampleDistance * i), pixelCoord.z);
					float jitterRange = sampleDistance / 2;
					glm::vec3 jitter = glm::vec3(glm::linearRand(-jitterRange, jitterRange), glm::linearRand(-jitterRange, jitterRange), glm::linearRand(-jitterRange, jitterRange));
					s += jitter;
					Ray ray = Ray(glm::vec3(0.0f), glm::normalize(s));
					glm::vec3 sampleRadiance = TracePath(ray, *scene, 0);
					//glm::vec3 sampleRadiance = DebugTrace(ray, *scene);

					radiance += sampleRadiance;
				}
			}

			radiance /= samples * samples;

			// Pixels is an array of 1 byte unsiged ints, so clamp values to 255 to prevent overflows
			pixels[((x + (y * width)) * 3)]		= glm::min(radiance.x * 255, 255.0f);
			pixels[((x + (y * width)) * 3) + 1] = glm::min(radiance.y * 255, 255.0f);
			pixels[((x + (y * width)) * 3) + 2] = glm::min(radiance.z * 255, 255.0f);
		}
	}

	stbi_write_bmp(path.data(), width, height, 3, pixels);
	spdlog::info("Done");

	// Opening image file:
	system(path.data());
}
