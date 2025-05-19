//
// Created by tanhao on 2025/5/9.
//

#ifndef OPENGLSHADER_H
#define OPENGLSHADER_H


#include "Hazel/Renderer/Shader.h"
#include "glm/glm.hpp"

typedef unsigned int GLenum;

namespace Hazel
{
    class HAZEL_API OpenglShader:public Shader{

    public:
        OpenglShader(const std::string& filepath);
        OpenglShader(const std::string name, const std::string& vertexSrc,const std::string fragmentSrc);

        ~OpenglShader();

       virtual void Bind() const override;
       virtual void Unbind() const override;

        virtual const std::string& GetName() const  override {return m_Name;}


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
        std::string m_Name;

    };
}

#endif //OPENGLSHADER_H
