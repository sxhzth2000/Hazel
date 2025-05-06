
//
// Created by tanhao on 2025/5/1.
//
#include "hzpch.h"

#include "RenderCommand.h"
#include "OpenGL/OpenGLRendererAPI.h"

namespace Hazel
{
    RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI;

    void RenderCommand::DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray)
    {
            s_RendererAPI->DrawIndexed(vertexArray);
    }

    void RenderCommand::SetClearColor(const glm::vec4& color)
    {
            s_RendererAPI->SetClearColor(color);
    }

    void RenderCommand::Clear()
    {
            s_RendererAPI->Clear();
    }

}
