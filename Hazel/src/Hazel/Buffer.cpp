//
// Created by tanhao on 2025/4/29.
//
#include "hzpch.h"

#include "Buffer.h"

#include "Core/Log.h"
#include "OpenGL/OpenglBuffer.h"
#include "Renderer/Renderer.h"

namespace Hazel {

    VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size)
    {
        switch (Renderer::GetAPI())
        {
        case RendererAPI::None: HZ_CORE_WARN("RendererAPI::None is currently not supported!"); return nullptr;
        case RendererAPI::OpenGL: return new Hazel::OpenglVertexBuffer(vertices,size);
        }
    }

    IndexBuffer* IndexBuffer::Create(unsigned int* indices, uint32_t count)
    {
        switch (Renderer::GetAPI())
        {
        case RendererAPI::None: HZ_CORE_WARN("RendererAPI::None is currently not supported!"); return nullptr;
        case RendererAPI::OpenGL: return new Hazel::OpenglIndexBuffer(indices,count);
        }
    }
} // Hazel