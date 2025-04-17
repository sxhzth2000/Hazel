#pragma once

#include <Hazel/Events/ApplicationEvent.h>

#include "Core.h"
#include "Window.h"
namespace Hazel {


	class HAZEL_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);
	private:
		bool OnWindowClose(WindowCloseEvent& e);
		std::unique_ptr<Window> m_Window;
		bool m_runing =true;

	};


	//To be defined int CLIENT
	Application* CreateApplication();

}