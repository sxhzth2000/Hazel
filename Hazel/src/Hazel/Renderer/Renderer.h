//
// Created by tanhao on 2025/4/29.
//

#ifndef RENDERER_H
#define RENDERER_H

#include <imgui.h>

#include "RendererAPI.h"
#include "RenderCommand.h"
#include "Shader.h"
#include "Hazel/Renderer/OrthographicCamera.h"
namespace Hazel
{

    class HAZEL_API Renderer {

    public:

        static void Init();
        static void OnWindowResize(uint32_t width,uint32_t height);
        static void BeginScene(OrthographicCamera& camera);
        static void EndScene();
        static  void Submit(const std::shared_ptr<Shader>& shader,const std::shared_ptr<VertexArray>& vertexArray,const glm::mat4 transform);
        inline static   RendererAPI::API GetAPI() {return RendererAPI::GetAPI();}

    private:
        struct SceneData
        {
            glm::mat4 ViewProjectionMatrix;
        };

        static SceneData* m_SceneData;

    };
}


#endif //RENDERER_H
