#include "hzpch.h"

#include <Hazel/Events/Event.h>

#include "Log.h"
#include <spdlog/fmt/ostr.h>

#include "Hazel/Core/Application.h"

#include <Windows/WindowsInput.h>

#include "Hazel/Events/ApplicationEvent.h"

#include "glad/glad.h"
#include "Hazel/Renderer/RenderCommand.h"


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

////first shape//
		m_VertexArray.reset(VertexArray::Create());
		float vertices[3*6]={
			-0.5f,-0.5f,  0.5f, 1.0f, 0.0f, 0.0f,
			 0.5f,-0.5f,  0.5f, 0.0f, 1.0f, 0.0f,
			 0.0f, 0.5f,  0.5f, 0.0f, 0.0f, 1.0f,
		};

		m_VertexBuffer.reset(VertexBuffer::Create(vertices,sizeof(vertices)));
			BufferLayout layout={
				{ShaderDataType::Float3,"a_Position"},
				{ShaderDataType::Float3,"a_color"}
			};
		m_VertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(m_VertexBuffer);

		unsigned int indices[3]={0,1,2};
		m_IndexBuffer.reset(IndexBuffer::Create(indices,sizeof(indices)/sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(m_IndexBuffer);

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




//second shape//
		m_SquareVA.reset(VertexArray::Create());
		float vertices_Square[4*6]={
			-0.75f,-0.75f, 0.0f, 1.0f, 0.0f, 0.0f,	//0
			 0.75f,-0.75f, 0.0f, 0.0f, 1.0f, 0.0f,	//1
			 0.75f, 0.75f, 0.0f, 0.0f, 0.0f, 1.0f,	//2
			-0.75f, 0.75f, 0.0f, 0.0f, 0.0f, 0.0f	//3
		};

		m_SquareVB.reset(VertexBuffer::Create(vertices_Square,sizeof(vertices_Square)));
		BufferLayout layout_square={
			{ShaderDataType::Float3,"a_Position"},
			{ShaderDataType::Float3,"a_color"}
		};
		m_SquareVB->SetLayout(layout_square);
		m_SquareVA->AddVertexBuffer(m_SquareVB);

		unsigned int indices_Square[2*3]={	0,1,2,
											2,3,0	};
		m_SquareIB.reset(IndexBuffer::Create(indices_Square,sizeof(indices_Square)/sizeof(uint32_t)));
		m_SquareVA->SetIndexBuffer(m_SquareIB);


		std::string vertexSrc_Square= R"(
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

		std::string fragmentSrc_Square= R"(
			#version 330 core
			layout(location = 0) out vec4 color;
			in vec3 v_color;
			void main()
			{
				color = vec4 (v_color,1.0);
			}
		)";
		m_Shader_Square.reset(new Shader(vertexSrc_Square,fragmentSrc_Square));

	}

	Application::~Application()
	{

	}

	void Application::Run()
	{
		while(m_runing)
		{
			RenderCommand::SetClearColor({0.2,0.3,0.4,1});

			RenderCommand::Clear();

			Renderer::BeginScene();
			{

				m_Shader_Square->Bind();
				Renderer::Submit(m_SquareVA);
				m_Shader->Bind();
				Renderer::Submit(m_VertexArray);
			}
			Renderer::EndScene();



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
