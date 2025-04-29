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




		float vertices[3*6]={
			-0.5f,-0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
			 0.5f,-0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
			 0.0f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f,
		};


		m_VertexBuffer.reset(VertexBuffer::Create(vertices,sizeof(vertices)));
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,6*sizeof(float),nullptr);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,6*sizeof(float),(void*)(3*sizeof(float)));


		unsigned int indices[3]={0,1,2};
		m_IndexBuffer.reset(IndexBuffer::Create(indices,sizeof(indices)/sizeof(uint32_t)));


		std::string vertexSrc= R"(
			#version 330 core
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec3 a_color;
			out vec3 v_color;

			void main()
			{
				gl_Position=vec4(a_Position,1.0);
				v_color = a_color;
			}
		)";

		std::string fragmentSrc= R"(
			#version 330 core
			layout(location = 0) out vec4 color;
			in vec3 v_color;
			void main()
			{
				color = vec4 (v_color,1.0);
			}
		)";

		m_Shader.reset(new Shader(vertexSrc,fragmentSrc));


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
			m_Shader->Bind();

			glBindVertexArray(m_VertexArraay);
			glDrawElements(GL_TRIANGLES,m_IndexBuffer->GetCount(),GL_UNSIGNED_INT,nullptr);

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
