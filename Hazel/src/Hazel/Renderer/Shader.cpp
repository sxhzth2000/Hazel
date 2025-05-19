//
// Created by tanhao on 2025/4/27.
//

#include "hzpch.h"
#include "Shader.h"

#include "OpenglShader.h"
#include "Renderer.h"
#include "glm/gtc/type_ptr.hpp"
#include "OpenGL/OpenGLVertexArray.h"

namespace Hazel{
    Ref<Shader> Shader::Create(const std::string& filepath)
    {
        switch (Renderer::GetAPI())
        {
        case RendererAPI::API::None: HZ_CORE_WARN("RendererAPI::None is currently not supported!"); return nullptr;
        case RendererAPI::API::OpenGL: return std::make_shared<OpenglShader> (filepath);
        }
        HZ_CORE_ASSERT(false,"Unknow RenderAPI!");
        return nullptr;
    }

    Ref<Shader> Shader::Create(const std::string& name, const std::string& vertexSrc, const std::string fragmentSrc)
    {

            switch (Renderer::GetAPI())
            {
            case RendererAPI::API::None: HZ_CORE_WARN("RendererAPI::None is currently not supported!"); return nullptr;
            case RendererAPI::API::OpenGL: return std::make_shared<OpenglShader> (name, vertexSrc,fragmentSrc);
            }
            HZ_CORE_ASSERT(false,"Unknow RenderAPI!");
            return nullptr;

    }


    void ShaderLibrary::Add(const std::string& name, const Ref<Shader>& shader)
    {

        HZ_CORE_ASSERT(!Exists(name), "Shader already exists!")
        m_Shaders[name] = shader;
    }

    void ShaderLibrary::Add(const Ref<Shader>& shader)
    {
        auto& name = shader->GetName();
        Add(name,shader);
    }



    Ref<Shader> ShaderLibrary::Load(const std::string& filepath)
    {
        auto shader = Shader::Create(filepath);
        Add(shader);
        return shader;
    }

    Ref<Shader> ShaderLibrary::Load(const std::string& name, const std::string& filepath)
    {
        auto shader = Shader::Create(filepath);
        Add(shader);
        return shader;
    }

    Ref<Shader> ShaderLibrary::Get(const std::string& name)
    {
        HZ_CORE_ASSERT(Exists(name), "Shader not found")

        return m_Shaders[name];
    }

    bool ShaderLibrary::Exists(const std::string& name) const
    {
        return m_Shaders.find(name) != m_Shaders.end();
    }
}
