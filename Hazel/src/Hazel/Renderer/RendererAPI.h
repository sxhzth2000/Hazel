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

    class HAZEL_API RendererAPI
    {


    public:
        enum class API
        {
            None = 0, OpenGL
        };
    public:

        RendererAPI(){};

        virtual void Init()=0;
        virtual void SetClearColor(const glm::vec4& color)=0;

        virtual  void  SetViewport(uint32_t x,uint32_t y,uint32_t width,uint32_t height)=0;

        virtual void Clear(){};

        virtual void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray){};

        inline static API GetAPI() ;

    private:

        static API s_API;
    };


}



#endif //RENDERAPI_H
