//
// Created by tanhao on 2025/5/9.
//

#ifndef OPENGLSHADER_H
#define OPENGLSHADER_H

#include "GLFW/src/internal.h"
#include "Hazel/Renderer/Shader.h"



namespace Hazel
{
    class HAZEL_API OpenglShader:public Shader{

    public:
        OpenglShader(const std::string& filepath);
        OpenglShader(const std::string& vertexSrc,const std::string fragmentSrc);

        ~OpenglShader();

       virtual void Bind() const override;
       virtual void Unbind() const override;


        void UploadUniformInt(const std::string& name, const unsigned value);

        void UploadUniformFloat1(const std::string& name, const float value);

        void UploadUniformFloat2(const std::string& name, const glm::vec2& value);

        void UploadUniformFloat3(const std::string& name, const glm::vec3& value);

        void UploadUniformFloat4(const std::string& name, const glm::vec4& value);

        void UploadUniformMat3(const std::string& name , const glm::mat3& matrix);
        void UploadUniformMat4(const std::string& name , const glm::mat4& matrix);


    private:

        std::string ReadFile( const std::string& filepath );
        std::unordered_map<GLenum,std::string> PreProcess(const std::string& source);
        void Compile(const std::unordered_map<GLenum,std::string>& shaderSources);
        static GLenum ShaderTypeFromString(const std::string& type);

    private:
        uint32_t m_RendererID;

    };
}

#endif //OPENGLSHADER_H
