//
// Created by tanhao on 2025/5/1.
//

#ifndef VERTEXARRAY_H
#define VERTEXARRAY_H

#include <memory>
#include <Hazel/Renderer/Buffer.h>

namespace Hazel
{
    class HAZEL_API VertexArray {

    public:
        virtual ~VertexArray(){}

        virtual void Bind() const=0;
        virtual void Unbind() const=0;

        virtual void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer)=0;
        virtual void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer)=0;

        virtual  const std::vector<Ref<VertexBuffer>>& GetVertexBuffers()const=0;
        virtual  const Ref<IndexBuffer>& GetIndexBuffer() const=0;

        static Ref<VertexArray> VertexArray::Create();

    };
}
#endif //VERTEXARRAY_H
