#include <Hazel/Events/Event.h>

#include "Log.h"
#include <spdlog/fmt/ostr.h>

#include "Hazel/Core/Application.h"
#include "Hazel/Events/ApplicationEvent.h"


#include <iostream>
#include <GL/gl.h>


namespace Hazel {

	Application::Application()
	{
		m_Window =  std::unique_ptr<Window>(Window::Create());
	}

	Application::~Application()
	{

	}

	void Application::Run()
	{
		while(m_runing)
		{


			glClearColor(1,0,1,1);
			glClear(GL_COLOR_BUFFER_BIT);
			m_Window->OnUpdate();
		}


	}

}
