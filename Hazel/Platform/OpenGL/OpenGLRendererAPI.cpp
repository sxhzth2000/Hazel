//
// Created by tanhao on 2025/5/1.
//
#include "hzpch.h"

#include "glad/glad.h"
#include "OpenGLRendererAPI.h"

#include <GL/gl.h>
#include <GL/gl.h>

void Hazel::OpenGLRendererAPI::Init()
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
}

void Hazel::OpenGLRendererAPI::SetClearColor(const glm::vec4& color)
{
    glClearColor(color.r,color.g,color.b,color.a);

}

void Hazel::OpenGLRendererAPI::SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
{
    HZ_INFO("glViewport");
  //  glViewport(x,y,width,height);
}

void Hazel::OpenGLRendererAPI::Clear()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Hazel::OpenGLRendererAPI::DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray)
{
    glDrawElements(GL_TRIANGLES,vertexArray->GetIndexBuffer()->GetCount(),GL_UNSIGNED_INT,nullptr);
}
