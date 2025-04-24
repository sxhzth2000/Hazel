#include "hzpch.h"

#include <Hazel/Events/Event.h>

#include "Log.h"
#include <spdlog/fmt/ostr.h>

#include "Hazel/Core/Application.h"

#include <Windows/WindowsInput.h>

#include "Hazel/Events/ApplicationEvent.h"


#include "glad/glad.h"



namespace Hazel {

#define BIND_EVENT_FN(x) std::bind(& Application::x,this,std::placeholders::_1)


	Application* Application::s_Instance=nullptr;


	Application::Application()
	{
		Input::s_Instance = new WindowsInput();

		s_Instance=this;
		if (!s_Instance)
			HZ_CORE_ERROR("Applicaton already exists!");
		m_Window =  std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));

		m_ImGuiLayer=new ImGuiLayer();
		PushLayer(m_ImGuiLayer);

		glGenVertexArrays(1,&m_VertexArraay);
		glBindVertexArray(m_VertexArraay);

		glGenBuffers(1,&m_VertexBuffer);
		glBindBuffer(GL_ARRAY_BUFFER,m_VertexBuffer);

		float vertices[3*3]={
			-0.5f,-0.5f, 0.0f,
			 0.5f,-0.5f, 0.0f,
			 0.0f, 0.5f, 0.0f
		};

		glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3*sizeof(float),nullptr);

		glGenBuffers(1,&m_IndexBuffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,m_IndexBuffer);

		unsigned int indices[3]={0,1,2};
		glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(indices),indices,GL_STATIC_DRAW);






	}

	Application::~Application()
	{

	}

	void Application::Run()
	{
		while(m_runing)
		{


			glClearColor(0.2,0.3,0.4,1);
			glClear(GL_COLOR_BUFFER_BIT);

			glBindVertexArray(m_VertexArraay);
			glDrawElements(GL_TRIANGLES,3,GL_UNSIGNED_INT,nullptr);

			for(Layer* layer:m_LayerStack)
				layer->OnUpdate();

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
