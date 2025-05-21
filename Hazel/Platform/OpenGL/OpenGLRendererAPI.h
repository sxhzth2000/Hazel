//
// Created by tanhao on 2025/5/1.
//

#ifndef OPENGLRENDERERAPI_H
#define OPENGLRENDERERAPI_H
#include "Hazel/Renderer/RendererAPI.h"

namespace Hazel{
class OpenGLRendererAPI : public RendererAPI
{

public:

    OpenGLRendererAPI(){};
    virtual void Init() override;
    virtual void SetClearColor(const glm::vec4& color) override;
    virtual void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) override;
    virtual void Clear()override;

    virtual void DrawIndexed(const Ref <VertexArray>& vertexArray)override;

};

}

#endif //OPENGLRENDERERAPI_H
