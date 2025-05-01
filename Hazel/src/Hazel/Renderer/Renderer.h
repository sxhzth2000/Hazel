//
// Created by tanhao on 2025/4/29.
//

#ifndef RENDERER_H
#define RENDERER_H

#include <imgui.h>

#include "RenderreAPI.h"
#include "RenderCommand.h"

namespace Hazel
{

    class Renderer {

    public:

        static void BeginScene();
        static void EndScene();

        static  void Submit(const std::shared_ptr<VertexArray>& vertexArray);
        inline static   RendererAPI::API GetAPI() {return RendererAPI::GetAPI();}

    private:


    };
}


#endif //RENDERER_H
