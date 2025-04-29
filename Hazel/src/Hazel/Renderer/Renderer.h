//
// Created by tanhao on 2025/4/29.
//

#ifndef RENDERER_H
#define RENDERER_H

namespace Hazel
{
    enum class RendererAPI
    {
        None=0,OpenGL = 1
    };
    class Renderer {

    public:
        inline static   RendererAPI GetAPI(){return s_RendererAPI;}
    private:
        static RendererAPI s_RendererAPI;

    };
}


#endif //RENDERER_H
