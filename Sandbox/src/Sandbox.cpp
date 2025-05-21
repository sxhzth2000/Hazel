
#include "Hazel/Core/EntryPoint.h"
#include <Hazel.h>
#include <imgui.h>



#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/type_ptr.inl>
#include <Hazel/OrthographicCameraController.h>

#include "../../Hazel/vendor/GLFW/include/GLFW/glfw3.h"
#include "Hazel/Renderer/Texture.h"


class ExampleLayer:public Hazel::Layer
{
public:
	ExampleLayer()
		:Layer("Example"),m_Camera_Controller(1280.0f / 720.0f)
	{
////first shape//
using namespace Hazel;




		m_Flat_VAO.reset(VertexArray::Create());
		float vertices[5*4]={
			-0.5f,-0.5f,  0.0f, 0, 0,
			 0.5f,-0.5f,  0.0f, 1, 0,
			 0.5f, 0.5f,  0.0f, 1, 1,
			-0.5f, 0.5f,  0.0f, 0, 1,
		};

		m_Flat_VBO.reset(VertexBuffer::Create(vertices,sizeof(vertices)));
			BufferLayout layout={
				{ShaderDataType::Float3,"a_Position"},
				{ShaderDataType::Float2,"a_TexCoord"}
			};
		m_Flat_VBO->SetLayout(layout);
		m_Flat_VAO->AddVertexBuffer(m_Flat_VBO);

		unsigned int indices[2*3]={	0,1,2,
									2,0,3	};

		m_Flat_IBO.reset(IndexBuffer::Create(indices,sizeof(indices)/sizeof(uint32_t)));
		m_Flat_VAO->SetIndexBuffer(m_Flat_IBO);



		std::string TextureShaderVertexSrc= R"(
			#version 330 core
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec2 a_TexCoord;
			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;
			out vec2 v_TexCoord;

			void main()
			{
				gl_Position=u_ViewProjection * u_Transform * vec4(a_Position,1.0);
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



		//second shape//
		m_Square_VAO.reset(VertexArray::Create());

		float vertices_Square[4*5]={
			-0.50f,-0.50f, 0.0f,	//0
			 0.50f,-0.50f, 0.0f,	//1
			 0.50f, 0.50f, 0.0f,	//2
			-0.50f, 0.50f, 0.0f,	//3
		};

		m_Square_VBO.reset(VertexBuffer::Create(vertices_Square,sizeof(vertices_Square)));
		BufferLayout layout_square={
			{ShaderDataType::Float3,"a_Position"},
		};
		m_Square_VBO->SetLayout(layout_square);
		m_Square_VAO->AddVertexBuffer(m_Square_VBO);

		unsigned int indices_Square[2*3]={	0,1,2,
											2,3,0	};
		m_Square_IBO.reset(IndexBuffer::Create(indices_Square,sizeof(indices_Square)/sizeof(uint32_t)));
		m_Square_VAO->SetIndexBuffer(m_Square_IBO);



/////////////////////////////////////////

		//this shader in shader
		m_Flat=Hazel::Shader::Create("Flat",TextureShaderVertexSrc,TextureShaderFragmentSrc);

		auto m_Square= m_ShaderLibrary.Load("assets/shaders/Texture.glsl");





		m_Flat->Bind();
		std::dynamic_pointer_cast<Hazel::OpenglShader>(m_Flat)->UploadUniformMat4("u_Texture",0);

		m_Texture=(Hazel::Texture2D::Create("assets/textures/Checkerboard.png"));
		m_ChernologoTexture=(Hazel::Texture2D::Create("assets/textures/ChernoLogo.png"));


	}

	void OnUpdate(Hazel::TimeStep ts) override
	{
		m_Camera_Controller.OnUpdate(ts);



		Hazel::RenderCommand::SetClearColor(color);
		Hazel::RenderCommand::Clear();

		Hazel::Renderer::BeginScene(m_Camera_Controller.GetCamera());
		{
			//





			glm::mat4 scale = glm::scale(glm::mat4(1.0f),glm::vec3 (0.1f));

			auto m_Square = m_ShaderLibrary.Get("Texture");

			m_Square->Bind();
			std::dynamic_pointer_cast<Hazel::OpenglShader>(m_Square)->UploadUniformFloat3("u_color",m_SquareColor);


			for (int i =-m_SquareNumber[0] ; i < m_SquareNumber[0] ; i++)
			{
				for (int j = -m_SquareNumber[1] ; j<m_SquareNumber[1] ; j++)
				{
					glm::vec3 pos(i * 0.12f,j *0.12f,0);
					glm::mat4 transform = glm::translate(glm::mat4(1.0f),m_Square_Transform + pos) * scale;
					m_Square->Bind()	;
					Hazel::Renderer::Submit(m_Square,m_Square_VAO,transform);
				}
			}


///////////////////////////////////////


			m_Flat->Bind();
			std::dynamic_pointer_cast<Hazel::OpenglShader>(m_Flat)->UploadUniformFloat3("u_color",m_Color);


			glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_ChernologoTexture_Transform)
								* glm::scale(glm::mat4(1.0f), m_ChernologoTexture_Scale);

			m_Texture->Bind(0);

			Hazel::Renderer::Submit(m_Flat,m_Flat_VAO,transform);


			 transform = glm::translate(glm::mat4(1.0f), m_Texture_Transform)
					* glm::scale(glm::mat4(1.0f), m_Texture_Scale);


			m_ChernologoTexture->Bind(0);

			Hazel::Renderer::Submit(m_Flat,m_Flat_VAO,transform);


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

		ImGui::SliderFloat3("Texture 1 translate",glm::value_ptr(m_Texture_Transform),-1,1);
		ImGui::SliderFloat3("Texture 1 scale",glm::value_ptr(m_Texture_Scale),0,2);

		ImGui::SliderFloat3("Texture 2 translate",glm::value_ptr(m_ChernologoTexture_Transform),-1,1);
		ImGui::SliderFloat3("Texture 2 scale",glm::value_ptr(m_ChernologoTexture_Scale),0,2);



		ImGui::End();
	}
void OnEvent(Hazel::Event& e)
{
	m_Camera_Controller.OnEvent(e);
}

private:

	Hazel::ShaderLibrary m_ShaderLibrary;

	glm::vec4 color={0.2,0.3,0.4,1};


	Hazel::Ref <Hazel::Shader>  m_Flat;
	Hazel::Ref <Hazel::VertexArray> m_Flat_VAO;
	Hazel::Ref <Hazel::VertexBuffer> m_Flat_VBO;
	Hazel::Ref <Hazel::IndexBuffer> m_Flat_IBO;




	// Hazel::Ref <Hazel::Shader>  m_Square;
	Hazel::Ref <Hazel::VertexArray> m_Square_VAO;
	Hazel::Ref <Hazel::VertexBuffer> m_Square_VBO;
	Hazel::Ref <Hazel::IndexBuffer> m_Square_IBO;




	Hazel::Ref<Hazel::Texture2D> m_Texture;
	glm::vec3 m_Texture_Scale= glm::vec3(1.0f);
	glm::vec3 m_Texture_Transform= glm::vec3(0.0f);

	Hazel::Ref<Hazel::Texture2D> m_ChernologoTexture;
	glm::vec3 m_ChernologoTexture_Scale= glm::vec3(1.0f);
	glm::vec3 m_ChernologoTexture_Transform= glm::vec3(0.0f);



	Hazel::OrthographicCameraController m_Camera_Controller;


	glm::vec3 m_Square_Transform =glm::vec3(1.0f);



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

