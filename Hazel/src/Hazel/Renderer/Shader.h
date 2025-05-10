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
        ~Shader() = default;

        virtual void Bind() const=0;
        virtual void Unbind() const=0;

        static Shader* Create(const std::string& path);

        static Shader* Create(const std::string& vertexSrc,const std::string fragmentSrc);
    private:
        uint32_t m_RendererID;

    };
}


#endif //SHADER_H
