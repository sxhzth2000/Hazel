//
// Created by tanhao on 2025/4/29.
//

#ifndef OPENGLBUFFER_H
#define OPENGLBUFFER_H
#include "../../src/Hazel/Renderer/Buffer.h"
namespace Hazel {

    class OpenglVertexBuffer :public VertexBuffer
    {
    public:
        OpenglVertexBuffer (float* vertices,uint32_t size);

         ~OpenglVertexBuffer();

        virtual void Bind() const override;
        virtual void Unbind() const override;


        virtual void SetLayout(const BufferLayout& layout) override {m_Layout=layout;};
        virtual const BufferLayout& GetLayout() const override {return m_Layout;};
    private:
        uint32_t m_RenderID;

        BufferLayout m_Layout;

    };

    class OpenglIndexBuffer :public IndexBuffer
    {
    public:
        OpenglIndexBuffer (unsigned int * vertices,uint32_t count);

        ~OpenglIndexBuffer();

        virtual uint32_t GetCount() const {return m_Count;}
        virtual void Bind() const override;
        virtual void Unbind() const override;
    private:
        uint32_t m_RenderID;
        uint32_t m_Count;
    };

} // Hazel

#endif //OPENGLBUFFER_H
