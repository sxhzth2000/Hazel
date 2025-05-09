//
// Created by tanhao on 2025/5/9.
//

#ifndef OPENGLSHADER_H
#define OPENGLSHADER_H

#include "Hazel/Renderer/Shader.h"

namespace Hazel
{
    class HAZEL_API OpenglShader:public Shader{

    public:
        OpenglShader(const std::string& vertexSrc,const std::string fragmentSrc);

        ~OpenglShader();

       virtual void Bind() const override;
       virtual void Unbind() const override;




        void UploadUniformFloat1(const std::string& name, const float value);

        void UploadUniformFloat2(const std::string& name, const glm::vec2& value);

        void UploadUniformFloat3(const std::string& name, const glm::vec3& value);

        void UploadUniformFloat4(const std::string& name, const glm::vec4& value);

        void UploadUniformMat3(const std::string& name , const glm::mat3& matrix);
        void UploadUniformMat4(const std::string& name , const glm::mat4& matrix);





    private:
        uint32_t m_RendererID;

    };
}

#endif //OPENGLSHADER_H
