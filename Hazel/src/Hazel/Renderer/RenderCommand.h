//
// Created by tanhao on 2025/5/1.
//

#ifndef RENDERCOMMAND_H

#define RENDERCOMMAND_H

#include "Renderer.h"

namespace Hazel
{
    class HAZEL_API RenderCommand
    {
    public:
        inline static void Init();
        inline static void  DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray);
        inline static void  SetViewport(uint32_t x,uint32_t y,uint32_t width,uint32_t height);
        inline static void  SetClearColor(const glm::vec4& color);

        inline static void  Clear();


    private:
        static RendererAPI* s_RendererAPI;
    };
}



#endif //RENDERCOMMAND_H
