#pragma once

#ifdef HZ_PLATFORM_WINDOWS

#include "Application.h"
#include "Log.h"
#include <stdio.h>


extern Hazel::Application* Hazel::CreateApplication();


int main(int argc,char** argv)
{
	Hazel::Log::Init();


	HZ_CORE_TRACE("Initialized Log!");
	HZ_CORE_INFO("Hello!");

	char a[] = { "qweqweqwe" };
	HZ_INFO("{0} \n{1}\n {{}}\n {{\n }} ", a, a);
	//printf("hazel engine");
	auto app =Hazel::CreateApplication();
	app->Run();
	delete app;
}
#endif // HZ_PLATFORM_WINDOWS
 