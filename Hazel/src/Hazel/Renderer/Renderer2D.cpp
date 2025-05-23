//
// Created by tanhao on 2025/5/22.
//
#include "hzpch.h"
#include "Renderer2D.h"

#include <glm/ext/matrix_transform.hpp>

#include "OpenglShader.h"
#include "RenderCommand.h"
#include "Shader.h"
#include "VertexArray.h"

namespace Hazel
{

    struct Renderer2DStorage
    {
        Ref<VertexArray> QuadVertexArray;
        Ref<Shader> FlatColorShader;
    };

    static Renderer2DStorage* s_Data;

    void Renderer2D::Init()
    {
        s_Data = new Renderer2DStorage();
        s_Data->QuadVertexArray = VertexArray::Create();

        float squarVertices[3*4]={
            -0.5f,-0.5f,  0.0f,
             0.5f,-0.5f,  0.0f,
             0.5f, 0.5f,  0.0f,
            -0.5f, 0.5f,  0.0f,
        };

        Ref<VertexBuffer> squareVB;

        squareVB.reset(VertexBuffer::Create(squarVertices,sizeof(squarVertices)));
        squareVB->SetLayout({
            {ShaderDataType::Float3,"a_Position"},
        });

        s_Data->QuadVertexArray -> AddVertexBuffer(squareVB);

        unsigned int indices[2*3]={	0,1,2,
                                    2,0,3	};

        Ref<IndexBuffer> squareIB;

        squareIB.reset(IndexBuffer::Create(indices,sizeof(indices)/sizeof(uint32_t)));
        s_Data->QuadVertexArray->SetIndexBuffer(squareIB);

        s_Data->FlatColorShader = Shader::Create("assets/shaders/FlatColor.glsl");


    }

    void Renderer2D::Shutdown()
    {
        delete s_Data;
    }

    void Renderer2D::BeginScene(const OrthographicCamera& camera)
    {
        std::dynamic_pointer_cast<Hazel::OpenglShader>(s_Data->FlatColorShader)->Bind();
        std::dynamic_pointer_cast<Hazel::OpenglShader>(s_Data->FlatColorShader)->UploadUniformMat4(
            "u_ViewProjection",camera.GetViewProjectionMatrix());
        std::dynamic_pointer_cast<Hazel::OpenglShader>(s_Data->FlatColorShader)->UploadUniformMat4(
    "u_Transform",glm::mat4(1.0f));
    }

    void Renderer2D::EndScene()
    {
        Hazel::Renderer::Submit(s_Data->FlatColorShader,s_Data->QuadVertexArray,glm::scale(glm::mat4(1.0f),glm::vec3(1.5f)));
    }

    void Renderer2D::DrawQuad(const glm::vec2 position, const glm::vec2& size, const glm::vec4& color)
    {
        DrawQuad({position.x, position.y ,0.0f},size ,color);

    }

    void Renderer2D::DrawQuad(const glm::vec3 position, const glm::vec2& size, const glm::vec4& color)
    {
        std::dynamic_pointer_cast<Hazel::OpenglShader>(s_Data->FlatColorShader)->Bind();
        std::dynamic_pointer_cast<Hazel::OpenglShader>(s_Data->FlatColorShader)->UploadUniformFloat4("U_color",color);

        s_Data->QuadVertexArray->Bind();

        RenderCommand::DrawIndexed( s_Data->QuadVertexArray);
    }
}
