//
// Created by tanhao on 2025/5/1.
//

#ifndef RENDERCOMMAND_H

#define RENDERCOMMAND_H

#include "Renderer.h"

namespace Hazel
{
    class RenderCommand
    {
    public:
        inline static void  DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray)
        {
            s_RendererAPI->DrawIndexed(vertexArray);
        }

        inline static void SetClearColor(const glm::vec4& color)
        {
            s_RendererAPI->SetClearColor(color);
        }
        inline static void  Clear()
        {
            s_RendererAPI->Clear();
        }
    private:
        static RendererAPI* s_RendererAPI;
    };
}



#endif //RENDERCOMMAND_H
