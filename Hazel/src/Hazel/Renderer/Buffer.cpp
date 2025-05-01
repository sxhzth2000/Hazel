//
// Created by tanhao on 2025/4/29.
//
#include "../../hzpch.h"

#include "Buffer.h"

#include "Renderer.h"
#include "../Core/Log.h"
#include "../../../Platform/OpenGL/OpenglBuffer.h"

namespace Hazel {

    VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size)
    {
        switch (RendererAPI::GetAPI())
        {
        case RendererAPI::API::None: HZ_CORE_WARN("RendererAPI::None is currently not supported!"); return nullptr;
        case RendererAPI::API::OpenGL: return new Hazel::OpenglVertexBuffer(vertices,size);
        }
    }

    IndexBuffer* IndexBuffer::Create(unsigned int* indices, uint32_t count)
    {
        switch (Renderer::GetAPI())
        {
        case RendererAPI::API::None: HZ_CORE_WARN("RendererAPI::None is currently not supported!"); return nullptr;
        case RendererAPI::API::OpenGL: return new Hazel::OpenglIndexBuffer(indices,count);
        }
    }
} // Hazel