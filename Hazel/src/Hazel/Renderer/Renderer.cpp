//
// Created by tanhao on 2025/4/29.
//

#include "Renderer.h"

#include <glad/glad.h>

#include "OpenglShader.h"
#include "OrthographicCamera.h"

namespace Hazel
{

    Renderer::SceneData* Renderer::m_SceneData =new Renderer::SceneData;

    void Renderer::Init()
    {
        RenderCommand::Init();
    }

    void Renderer::OnWindowResize(uint32_t width, uint32_t height)
    {
        RenderCommand::SetViewport(0,0,width,height);
    }

    void Renderer::BeginScene(OrthographicCamera& camera)
    {
        m_SceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
       // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }

    void Renderer::EndScene()
    {
    }

    void Renderer::Submit(const std::shared_ptr<Shader>& shader,const std::shared_ptr<VertexArray>& vertexArray,const glm::mat4 transform)
    {
        shader->Bind();
        std::dynamic_pointer_cast<OpenglShader>(shader)->UploadUniformMat4("u_ViewProjection",m_SceneData->ViewProjectionMatrix);
        std::dynamic_pointer_cast<OpenglShader>(shader)->UploadUniformMat4("u_Transform",transform);

        vertexArray->Bind();
        RenderCommand::DrawIndexed(vertexArray);
    }


}
