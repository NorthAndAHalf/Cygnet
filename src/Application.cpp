#include "Application.h"
#include "spdlog/spdlog.h"

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
	spdlog::trace("DEBUG POG");
	spdlog::info("smelly");
}