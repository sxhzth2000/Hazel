
//
// Created by tanhao on 2025/5/1.
//
#include "hzpch.h"

#include "RenderCommand.h"
#include "OpenGL/OpenGLRendererAPI.h"

namespace Hazel
{
    RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI;

    void RenderCommand::Init()
    {
            s_RendererAPI->     Init();
    }

    void RenderCommand::DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray)
    {
            s_RendererAPI->DrawIndexed(vertexArray);
    }

    void RenderCommand::SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
    {
            s_RendererAPI->SetViewport(x,y,width,height);
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
