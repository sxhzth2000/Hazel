#include "hzpch.h"

#include <Hazel/Events/Event.h>

#include "Log.h"
#include <spdlog/fmt/ostr.h>

#include "Hazel/Core/Application.h"

#include <glm/gtc/type_ptr.hpp>
#include <Windows/WindowsInput.h>

#include "Hazel/Events/ApplicationEvent.h"

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "Hazel/Renderer/RenderCommand.h"

#include "Hazel/Renderer/OrthographicCamera.h"

namespace Hazel {

#define BIND_EVENT_FN(x) std::bind(& Application::x,this,std::placeholders::_1)



	Application* Application::s_Instance=nullptr;


	Application::Application()
	{
		Input::s_Instance = new WindowsInput();

		s_Instance=this;
		if (!s_Instance)
			HZ_CORE_ERROR("Applicaton already exists!");
		m_Window =  Scope <Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));

		m_ImGuiLayer=new ImGuiLayer();
		PushLayer(m_ImGuiLayer);


	}

	Application::~Application()
	{

	}

	void Application::Run()
	{



		while(m_runing)
		{
			float const time =static_cast<float>(glfwGetTime());

			TimeStep timestep = time - m_LastTime;
			m_LastTime=time;

			for(Layer* layer:m_LayerStack)
				layer->OnUpdate(timestep);


			m_ImGuiLayer->Begin();
			{
				for (Layer* layer:m_LayerStack)
					layer->OnImguiRender();
			}
			m_ImGuiLayer->End();


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

		for (auto it = m_LayerStack.end(); it!=m_LayerStack.begin();)
		{
			(*--it)->OnEvent(e);
			if(e.Handled)
				break;
		}
	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* layer)
	{
		m_LayerStack.PushOverlay(layer);
		layer->OnAttach();
	}

	Application& Application::Get()
	{
		return *s_Instance;
	}

	Window& Application::GetWindow()
	{
		return * m_Window;
	}
}
