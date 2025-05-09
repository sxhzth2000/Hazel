//
// Created by tanhao on 2025/4/29.
//

#include "Renderer.h"

#include "OpenglShader.h"
#include "OrthographicCamera.h"

namespace Hazel
{

    Renderer::SceneData* Renderer::m_SceneData =new Renderer::SceneData;

    void Renderer::BeginScene(OrthographicCamera& camera)
    {
        m_SceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
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
