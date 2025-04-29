//
// Created by tanhao on 2025/4/27.
//

#ifndef SHADER_H
#define SHADER_H


namespace Hazel
{
    class Shader {
    public:
        Shader(const std::string& vertexSrc,const std::string fragmentSrc);
        ~Shader();

        void Bind() const;
        void Unbind() const;
    private:
        uint32_t m_RendererID;
    };
}


#endif //SHADER_H
