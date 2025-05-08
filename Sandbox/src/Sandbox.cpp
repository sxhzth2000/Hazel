
#include "Hazel/Core/EntryPoint.h"
#include <Hazel.h>
#include <imgui.h>
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/type_ptr.inl>
#include "../../Hazel/vendor/GLFW/include/GLFW/glfw3.h"

class ExampleLayer:public Hazel::Layer
{
public:
	ExampleLayer()
		:Layer("Example"),m_Camera(-1.6,1.6,-0.9,0.9),
			m_CameraPosition(0.0),m_Transform(glm::vec3(0,0,0)),
			m_Square_Transform(glm::vec3 (0,0,0))
	{
////first shape//
using namespace Hazel;

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
			uniform mat4 u_ViewProjection;



			void main()
			{
				gl_Position=u_ViewProjection  * vec4(a_Position,1.0);
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
			-0.50f,-0.50f, 0.0f, 0.2f, 0.3f, 0.8f,	//0
			 0.50f,-0.50f, 0.0f, 0.2f, 0.3f, 0.8f,	//1
			 0.50f, 0.50f, 0.0f, 0.2f, 0.3f, 0.8f,	//2
			-0.50f, 0.50f, 0.0f, 0.2f, 0.3f, 0.8f	//3
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
			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;
			void main()
			{
				gl_Position= u_ViewProjection * u_Transform * vec4(a_Position,1.0);
				v_color = a_color;
			}
		)";

		std::string fragmentSrc_Square= R"(
			#version 330 core
			layout(location = 0) out vec4 color;
			in vec3 v_color;

			uniform vec4 u_color;

			void main()
			{
				color = vec4 (v_color,1.0);
			}
		)";
		m_Shader_Square.reset(new Shader(vertexSrc_Square,fragmentSrc_Square));
	}

	void OnUpdate(Hazel::TimeStep ts) override
	{

		HZ_TRACE("TimeStep: {0}s ({1}ms {2})",ts.GetSeconds(),ts.GetMilliseconds(), float(ts));


		if (Hazel::Input::IsKeyPressed(HZ_KEY_A))
		{
			m_CameraPosition.x-= m_CameraMoveSpeed*ts;
		}
		if (Hazel::Input::IsKeyPressed(HZ_KEY_D))
		{
			m_CameraPosition.x+= m_CameraMoveSpeed*ts;
		}
		if (Hazel::Input::IsKeyPressed(HZ_KEY_W))
		{
			m_CameraPosition.y+= m_CameraMoveSpeed*ts;
		}
		if (Hazel::Input::IsKeyPressed(HZ_KEY_S))
		{
			m_CameraPosition.y-= m_CameraMoveSpeed*ts;
		}

		if (Hazel::Input::IsKeyPressed(HZ_KEY_Q))
		{
			m_CameraRotation-= m_CameraRotationSpeed*ts;
		}
		if (Hazel::Input::IsKeyPressed(HZ_KEY_E))
		{
			m_CameraRotation+= m_CameraRotationSpeed*ts;
		}






		if (Hazel::Input::IsKeyPressed(HZ_KEY_UP))
		{
			m_Square_Transform.y+= m_CameraMoveSpeed*ts;
		}
		if (Hazel::Input::IsKeyPressed(HZ_KEY_DOWN))
		{
			m_Square_Transform.y-= m_CameraMoveSpeed*ts;
		}

		if (Hazel::Input::IsKeyPressed(HZ_KEY_LEFT))
		{
			m_Square_Transform.x-= m_CameraMoveSpeed*ts;
		}
		if (Hazel::Input::IsKeyPressed(HZ_KEY_RIGHT))
		{
			m_Square_Transform.x+= m_CameraMoveSpeed*ts;
		}











		Hazel::RenderCommand::SetClearColor(color);
		Hazel::RenderCommand::Clear();
		m_Camera.SetPosition(m_CameraPosition);
		m_Camera.SetRotation(m_CameraRotation);

		Hazel::Renderer::BeginScene(m_Camera);
		{



			glm::mat4 scale = glm::scale(glm::mat4(1.0f),glm::vec3 (0.1f));

			for (int i =-10 ; i < 10 ; i++)
			{
				glm::vec3 pos(i * 0.12f,0,0);

				glm::mat4 transform = glm::translate(glm::mat4(1.0f),m_Square_Transform + pos) * scale;

				m_Shader_Square->Bind();
				Hazel::Renderer::Submit(m_Shader_Square,m_SquareVA,transform);
			}





			m_Shader->Bind();
			Hazel::Renderer::Submit(m_Shader,m_VertexArray,glm::mat4(1.0f));
		}
		Hazel::Renderer::EndScene();

	}


	void OnImguiRender() override
	{
		ImGui::Begin("111");
		ImGui::ColorEdit4("Clear Color", glm::value_ptr(color));
		ImGui::End();
	}


private:
	glm::vec4 color={0.2,0.3,0.4,1};
	std::shared_ptr<Hazel::Shader>  m_Shader;
	std::shared_ptr<Hazel::VertexArray> m_VertexArray;
	std::shared_ptr<Hazel::VertexBuffer> m_VertexBuffer;
	std::shared_ptr<Hazel::IndexBuffer> m_IndexBuffer;

	std::shared_ptr<Hazel::Shader>  m_Shader_Square;
	std::shared_ptr<Hazel::VertexArray> m_SquareVA;
	std::shared_ptr<Hazel::VertexBuffer> m_SquareVB;
	std::shared_ptr<Hazel::IndexBuffer> m_SquareIB;

	Hazel::OrthographicCamera m_Camera;
	glm::vec3 m_CameraPosition;

	glm::vec3 m_Square_Transform;
	glm::vec3 m_Transform;

	float m_CameraRotation;


	float m_CameraMoveSpeed=5.0f;
	float m_CameraRotationSpeed=180.0f;

};



class Sandbox :public Hazel::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
	//	PushLayer(new Hazel::ImGuiLayer());
	}
	~Sandbox()
	{

	}
private:

};


Hazel::Application* Hazel::CreateApplication()
{
	return new Sandbox();
}

