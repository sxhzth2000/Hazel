#include <Hazel/Events/Event.h>

#include "Log.h"
#include <spdlog/fmt/ostr.h>

#include "Hazel/Core/Application.h"
#include "Hazel/Events/ApplicationEvent.h"


#include <iostream>


namespace Hazel {

	Application::Application()
	{

	}

	Application::~Application()
	{

	}

	void Application::Run()
	{
		WindowResizeEvent e(123,123);

		if (e.IsInCategory(EventCategoryApplication))
		{

			HZ_TRACE(e.ToString());
			HZ_INFO(e.ToString());
		}

		while (true);
	}

}