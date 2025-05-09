//
// Created by tanhao on 2025/4/27.
//

#include "hzpch.h"
#include "Shader.h"

#include "OpenglShader.h"
#include "Renderer.h"
#include "glad/glad.h"
#include "glm/gtc/type_ptr.hpp"
#include "OpenGL/OpenGLVertexArray.h"

namespace Hazel{






    Shader* Shader::Create(const std::string& vertexSrc, const std::string fragmentSrc)
    {

            switch (Renderer::GetAPI())
            {
            case RendererAPI::API::None: HZ_CORE_WARN("RendererAPI::None is currently not supported!"); return nullptr;
            case RendererAPI::API::OpenGL: return new OpenglShader(vertexSrc,fragmentSrc);
            }
            HZ_CORE_ASSERT(false,"Unknow RenderAPI!");
            return nullptr;

    }




}
