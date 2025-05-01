//
// Created by tanhao on 2025/5/1.
//

#ifndef OPENGLVERTEXARRAY_H
#define OPENGLVERTEXARRAY_H
#include <memory>
#include <vector>

#include "../../vendor/GLFW/src/internal.h"
#include "Hazel/Renderer/Buffer.h"
#include "Hazel/Renderer/VertexArray.h"

namespace Hazel
{
    class OpenGLVertexArray :public VertexArray{

    public:
        OpenGLVertexArray();
        virtual ~OpenGLVertexArray();
        virtual void Bind() const override;
        virtual void Unbind() const override;

        virtual void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer) override;
        virtual void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer) override;


        virtual  const std::vector<std::shared_ptr<VertexBuffer>>& GetVertexBuffers()const {return m_VertexBuffers;}
        virtual  const std::shared_ptr<IndexBuffer>& GetIndexBuffer() const {return m_IndexBuffers; }



    private:
        std::vector<std::shared_ptr<VertexBuffer>> m_VertexBuffers;
        std::shared_ptr<IndexBuffer> m_IndexBuffers;
        uint32_t m_RendererID;

    };


}
#endif //OPENGLVERTEXARRAY_H
