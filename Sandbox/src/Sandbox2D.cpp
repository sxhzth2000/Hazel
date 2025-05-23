//
// Created by tanhao on 2025/5/22.
//

#include "Sandbox2D.h"

#include <glm/ext/matrix_transform.hpp>

#include <glm/gtc/type_ptr.inl>


Sandbox2D::Sandbox2D()
	:Layer("Sandbox2D"),m_Camera_Controller(1280.0f / 720.0f)
{
}

void Sandbox2D::OnUpdate(Hazel::TimeStep ts)
{
	m_Camera_Controller.OnUpdate(ts);

	Hazel::RenderCommand::SetClearColor(color);
	Hazel::RenderCommand::Clear();

	Hazel::Renderer2D::Init();
	Hazel::Renderer2D::BeginScene(m_Camera_Controller.GetCamera());
	Hazel::Renderer2D::DrawQuad({0.0f , 0.0f},{1.0f,1.0f},{0.8f,0.2f,0.3f,1.0f});
	Hazel::Renderer2D::EndScene();



		//		std::dynamic_pointer_cast<Hazel::OpenglShader>(m_FlatColorShader)->Bind();
		//		std::dynamic_pointer_cast<Hazel::OpenglShader>(m_FlatColorShader)->UploadUniformFloat4("U_color",m_SquareColor);


}

void Sandbox2D::OnAttach()
{

}

void Sandbox2D::OnDetach()
{


}

void Sandbox2D::OnImguiRender()
{

    ImGui::Begin("Settings");

    ImGui::ColorEdit4("SquareColor",glm::value_ptr(m_SquareColor));

    ImGui::End();

}

void Sandbox2D::OnEvent(Hazel::Event& e)
{
    m_Camera_Controller.OnEvent(e);
}
