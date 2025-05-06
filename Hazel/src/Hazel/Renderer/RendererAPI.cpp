//
// Created by tanhao on 2025/5/1.
//

#include "RendererAPI.h"

#include "VertexArray.h"

namespace Hazel
{
    RendererAPI::API RendererAPI::s_API=RendererAPI::API::OpenGL;


    RendererAPI::API RendererAPI::GetAPI()
    {
        {return s_API;}
    }
}
