
#include "Hazel/Core/EntryPoint.h"
#include <Hazel.h>
#include <imgui.h>
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/type_ptr.inl>
#include "../../Hazel/vendor/GLFW/include/GLFW/glfw3.h"
#include "Hazel/Renderer/Texture.h"


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

		m_TextureShaderVertexArray.reset(VertexArray::Create());
		float vertices[5*4]={
			-0.5f,-0.5f,  0.0f, 0, 0,
			 0.5f,-0.5f,  0.0f, 1, 0,
			 0.5f, 0.5f,  0.0f, 1, 1,
			-0.5f, 0.5f,  0.0f, 0, 1,
		};

		m_TextureShaderVertexBuffer.reset(VertexBuffer::Create(vertices,sizeof(vertices)));
			BufferLayout layout={
				{ShaderDataType::Float3,"a_Position"},
				{ShaderDataType::Float2,"a_TexCoord"}
			};
		m_TextureShaderVertexBuffer->SetLayout(layout);
		m_TextureShaderVertexArray->AddVertexBuffer(m_TextureShaderVertexBuffer);

		unsigned int indices[2*3]={	0,1,2,
									2,0,3	};

		m_TextureShaderIndexBuffer.reset(IndexBuffer::Create(indices,sizeof(indices)/sizeof(uint32_t)));

		m_TextureShaderVertexArray->SetIndexBuffer(m_TextureShaderIndexBuffer);

		std::string TextureShaderVertexSrc= R"(
			#version 330 core
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec2 a_TexCoord;
			uniform mat4 u_ViewProjection;

			out vec2 v_TexCoord;

			void main()
			{
				gl_Position=u_ViewProjection  * vec4(a_Position,1.0);
				v_TexCoord = a_TexCoord;

			}
		)";

		std::string TextureShaderFragmentSrc= R"(
			#version 330 core
			layout(location = 0) out vec4 color;
			in vec2 v_TexCoord;

			uniform sampler2D u_Texture;

			void main()
			{
				color = texture(u_Texture,v_TexCoord);
			}
		)";

		m_TextureShader.reset(Hazel::Shader::Create(TextureShaderVertexSrc,TextureShaderFragmentSrc));

		 m_Texture=(Hazel::Texture2D::Create("assets/textures/Checkerboard.png"));
		m_TextureShader->Bind();

		std::dynamic_pointer_cast<Hazel::OpenglShader>(m_TextureShader)->UploadUniformMat4("u_Texture",0);

//second shape//
		m_SquareVA.reset(VertexArray::Create());

		float vertices_Square[4*5]={
			-0.50f,-0.50f, 0.0f,	//0
			 0.50f,-0.50f, 0.0f,	//1
			 0.50f, 0.50f, 0.0f,	//2
			-0.50f, 0.50f, 0.0f,	//3
		};

		m_SquareVB.reset(VertexBuffer::Create(vertices_Square,sizeof(vertices_Square)));
		BufferLayout layout_square={
			{ShaderDataType::Float3,"a_Position"},

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


			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			void main()
			{
				gl_Position= u_ViewProjection * u_Transform * vec4(a_Position,1.0);

			}
		)";

		std::string fragmentSrc_Square= R"(
			#version 330 core
			layout(location = 0) out vec4 color;

			uniform vec3 u_color;

			void main()
			{
				color = vec4( u_color,1.0f);
			}
		)";


		m_Shader_Square.reset( Hazel::Shader::Create(vertexSrc_Square,fragmentSrc_Square));
	}

	void OnUpdate(Hazel::TimeStep ts) override
	{



		//HZ_TRACE("TimeStep: {0}s ({1}ms {2})",ts.GetSeconds(),ts.GetMilliseconds(), float(ts));


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


			m_Shader_Square->Bind();
			std::dynamic_pointer_cast<Hazel::OpenglShader>(m_Shader_Square)->UploadUniformFloat3("u_color",m_SquareColor);


			for (int i =-m_SquareNumber[0] ; i < m_SquareNumber[0] ; i++)
			{
				for (int j = -m_SquareNumber[1] ; j<m_SquareNumber[1] ; j++)
				{
					glm::vec3 pos(i * 0.12f,j *0.12f,0);
					glm::mat4 transform = glm::translate(glm::mat4(1.0f),m_Square_Transform + pos) * scale;
					m_Shader_Square->Bind();
					Hazel::Renderer::Submit(m_Shader_Square,m_SquareVA,transform);
				}
			}


			m_TextureShader->Bind();
			std::dynamic_pointer_cast<Hazel::OpenglShader>(m_TextureShader)->UploadUniformFloat3("u_color",m_Color);

			m_TextureShader->Bind();
			m_Texture->Bind(0);
			Hazel::Renderer::Submit(m_TextureShader,m_TextureShaderVertexArray,glm::mat4(1.0f));

		}
		Hazel::Renderer::EndScene();

	}


	void OnImguiRender() override
	{
		ImGui::Begin("Settings");
		ImGui::ColorEdit4("Clear Color", glm::value_ptr(color));
		ImGui::ColorEdit3("SquareColor",glm::value_ptr(m_SquareColor));
		ImGui::SliderInt2("SquareNumber",m_SquareNumber,1,10);
		ImGui::ColorEdit3("Color",glm::value_ptr(m_Color));

		ImGui::End();
	}


private:
	glm::vec4 color={0.2,0.3,0.4,1};
	Hazel::Ref <Hazel::Shader>  m_TextureShader;
	Hazel::Ref <Hazel::VertexArray> m_TextureShaderVertexArray;
	Hazel::Ref <Hazel::VertexBuffer> m_TextureShaderVertexBuffer;
	Hazel::Ref <Hazel::IndexBuffer> m_TextureShaderIndexBuffer;

	Hazel::Ref <Hazel::Shader>  m_Shader_Square;
	Hazel::Ref <Hazel::VertexArray> m_SquareVA;
	Hazel::Ref <Hazel::VertexBuffer> m_SquareVB;
	Hazel::Ref <Hazel::IndexBuffer> m_SquareIB;

	Hazel::Ref<Hazel::Texture2D> m_Texture;

	Hazel::OrthographicCamera m_Camera;
	glm::vec3 m_CameraPosition;

	glm::vec3 m_Square_Transform;
	glm::vec3 m_Transform;

	float m_CameraRotation;


	float m_CameraMoveSpeed=5.0f;
	float m_CameraRotationSpeed=180.0f;

	glm::vec3 m_SquareColor= glm::vec3(0.8f,0.2f,0.3f);
	glm::vec3 m_Color= glm::vec3(0.6f,0.2f,0.3f);

	int m_SquareNumber[2]={4,4};

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

