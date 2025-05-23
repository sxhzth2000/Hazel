//
// Created by tanhao on 2025/5/22.
//

#ifndef RENDERER2D_H
#define RENDERER2D_H
#include "OrthographicCamera.h"

namespace Hazel
{
    class HAZEL_API Renderer2D {
    public:
        static  void Init();
        static void Shutdown();

        static void BeginScene(const OrthographicCamera& camera);
        static void EndScene();
    //Primitives
        static void DrawQuad(const glm::vec2 position,const glm::vec2& size, const glm::vec4& color);
        static void DrawQuad(const glm::vec3 position,const glm::vec2& size, const glm::vec4& color);
    };
}

#endif //RENDERER2D_H
