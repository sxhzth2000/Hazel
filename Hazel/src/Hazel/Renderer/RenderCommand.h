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
        inline static void  DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray);

        inline static void SetClearColor(const glm::vec4& color);

        inline static void  Clear();


    private:
        static RendererAPI* s_RendererAPI;
    };
}



#endif //RENDERCOMMAND_H
