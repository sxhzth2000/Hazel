//
// Created by tanhao on 2025/5/1.
//
#include "hzpch.h"

#include "glad/glad.h"
#include "OpenGLRendererAPI.h"

#include <GL/gl.h>

void Hazel::OpenGLRendererAPI::SetClearColor(const glm::vec4& color)
{
    glClearColor(color.r,color.g,color.b,color.a);

}

void Hazel::OpenGLRendererAPI::Clear()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Hazel::OpenGLRendererAPI::DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray)
{
    glDrawElements(GL_TRIANGLES,vertexArray->GetIndexBuffer()->GetCount(),GL_UNSIGNED_INT,nullptr);
}
