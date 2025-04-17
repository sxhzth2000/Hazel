#include "hzpch.h"

#include <Hazel/Events/Event.h>

#include "Log.h"
#include <spdlog/fmt/ostr.h>

#include "Hazel/Core/Application.h"
#include "Hazel/Events/ApplicationEvent.h"


#include <iostream>
#include <GL/gl.h>


namespace Hazel {

#define BIND_EVENT_FN(x) std::bind(& Application::x,this,std::placeholders::_1)

	Application::Application()
	{
		m_Window =  std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));
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

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_runing=false;

		return true;
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));

		HZ_CORE_TRACE("{0}",e.ToString());
	}


}
