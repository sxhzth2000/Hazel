//
// Created by tanhao on 2025/5/9.
//

#include "OpenGLTexture.h"

#include <glad/glad.h>

#include "stb_image/stb_image.h"
namespace Hazel
{
    Hazel::OpenGLTexture2D::OpenGLTexture2D(const std::string& path)
        :m_Path(path)
    {
        int width ,height, channels;
        stbi_set_flip_vertically_on_load(1);
        stbi_uc* data =  stbi_load(path.c_str(),&width,&height,&channels,0);
        HZ_CORE_ASSERT(data, "Failed to load image!");
        m_Width = width;
        m_Height = height;
        GLenum internalformat=0, dataForamt=0;

        if (channels==4)
        {
            internalformat =GL_RGBA8;
            dataForamt = GL_RGBA;
        }
        else if (channels ==3)
        {
            internalformat = GL_RGB8;
            dataForamt = GL_RGB;

        }

        glCreateTextures(GL_TEXTURE_2D,1,&m_RendererID);
        glTextureStorage2D(m_RendererID,1,internalformat,m_Width,m_Height);

        glTextureParameteri(m_RendererID,GL_TEXTURE_MIN_FILTER,GL_LINEAR);  //
        glTextureParameteri(m_RendererID,GL_TEXTURE_MAG_FILTER,GL_NEAREST);  //放大缩小过程，用什么技术，线性插值会模糊，临近会清晰

        glTextureSubImage2D(m_RendererID,0,0,0,m_Width,m_Height,dataForamt,GL_UNSIGNED_BYTE,data);

        stbi_image_free(data);
    }

    Hazel::OpenGLTexture2D::~OpenGLTexture2D()
    {
        glDeleteTextures(1,&m_RendererID);
    }

    void Hazel::OpenGLTexture2D::Bind(uint32_t slot) const
    {
        glBindTextureUnit(slot,m_RendererID);
    }
}