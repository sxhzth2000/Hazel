//
// Created by tanhao on 2025/5/9.
//

#include "hzpch.h"
#include "Texture.h"

#include "Hazel/Renderer/Renderer.h"
#include "OpenGL/OpenGLTexture.h"
Hazel::Ref<Hazel::Texture2D> Hazel::Texture2D::Create(const std::string path)
{

        switch (Renderer::GetAPI())
        {
        case RendererAPI::API::None: HZ_CORE_WARN("RendererAPI::None is currently not supported!"); return nullptr;
        case RendererAPI::API::OpenGL: return std::make_shared<OpenGLTexture2D>(path);
        }
        HZ_CORE_ASSERT(false,"Unknow RenderAPI!");
        return nullptr;


}
