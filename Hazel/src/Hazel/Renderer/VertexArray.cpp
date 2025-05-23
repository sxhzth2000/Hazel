//
// Created by tanhao on 2025/5/1.
//

#include "hzpch.h"
#include "Hazel/Renderer/Buffer.h"
#include "Hazel/Renderer/Renderer.h"
#include "OpenGL/OpenGLBuffer.h"
#include "VertexArray.h"

#include "OpenGL/OpenGLVertexArray.h"

namespace Hazel
{
    Ref<VertexArray> VertexArray::Create()
    {
        switch (Renderer::GetAPI())
        {
        case RendererAPI::API::None: HZ_CORE_WARN("RendererAPI::None is currently not supported!"); return nullptr;
        case RendererAPI::API::OpenGL: return std::make_shared<OpenGLVertexArray>();
        }
        HZ_CORE_ASSERT(false,"Unknow RenderAPI!");
        return nullptr;

    }
}
