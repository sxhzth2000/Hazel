//
// Created by tanhao on 2025/4/29.
//

#ifndef BUFFER_H
#define BUFFER_H

namespace Hazel {

    class  VertexBuffer {
    public:
        virtual ~VertexBuffer(){};

        virtual void Bind() const=0;
        virtual void Unbind() const=0;
        static VertexBuffer* Create(float* vertices,uint32_t size);

    };

    class  IndexBuffer
    {
    public:
        virtual ~IndexBuffer(){};

        virtual void Bind() const=0;
        virtual void Unbind() const=0;
        virtual  uint32_t GetCount() const=0;
        static IndexBuffer* Create(unsigned int * indices,uint32_t count);
    };

} // Hazel

#endif //BUFFER_H
