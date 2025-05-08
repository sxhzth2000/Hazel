//
// Created by tanhao on 2025/4/27.
//

#ifndef SHADER_H
#define SHADER_H

#include "glm/glm.hpp"
namespace Hazel
{
    class HAZEL_API Shader {
    public:
        Shader(const std::string& vertexSrc,const std::string fragmentSrc);
        ~Shader();

        void Bind() const;
        void Unbind() const;

        void UploadUniformMat4(const std::string& name , const glm::mat4& matrix);

    private:
        uint32_t m_RendererID;

    };
}


#endif //SHADER_H
