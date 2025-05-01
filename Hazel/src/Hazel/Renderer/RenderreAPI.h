//
// Created by tanhao on 2025/5/1.
//

#ifndef RENDERAPI_H
#define RENDERAPI_H
#include <memory>

#include "VertexArray.h"
#include "glm/glm.hpp"
namespace Hazel
{

    class RendererAPI
    {


    public:
        enum class API
        {
            None = 0, OpenGL
        };
    public:
        RendererAPI() = default;
        virtual void SetClearColor(const glm::vec4& color){};
        virtual void Clear(){};

        virtual void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray){};

        inline static API GetAPI() {return s_API;}

    private:

        static API s_API;
    };

}



#endif //RENDERAPI_H
