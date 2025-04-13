#pragma once


#ifdef HZ_PLATFORM_WINDOWS

#include "Log.h"
#include "Application.h"

extern Hazel::Application* Hazel::CreateApplication();

int main(int argc,char** argv)
{
	spdlog::info("Hellow spdlog!");

	Hazel::Log::Init();


	HZ_TRACE	("Hellow HazelLog!");


	auto app =Hazel::CreateApplication();
	app->Run();
	delete app;
	return 0;
}
#endif // HZ_PLATFORM_WINDOWS
 