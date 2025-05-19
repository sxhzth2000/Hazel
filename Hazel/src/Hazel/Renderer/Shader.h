//
// Created by tanhao on 2025/4/27.
//

#ifndef SHADER_H
#define SHADER_H



#include <unordered_map>

namespace Hazel
{
    class HAZEL_API Shader {
    public:
        ~Shader() = default;

        virtual void Bind() const=0;
        virtual void Unbind() const=0;
        virtual const std::string& GetName() const = 0;

        static Ref<Shader> Create(const std::string& path);

        static Ref<Shader> Create(const std::string& name, const std::string& vertexSrc,const std::string fragmentSrc);


    };

    class HAZEL_API ShaderLibrary
    {
    public:
        void Add(const Ref<Shader>& shader);
        void Add(const std::string& name ,const Ref<Shader>& shader);
        Ref<Shader> Load(const std::string& filepath);
        Ref<Shader> Load(const std::string& name, const std::string& filepath);

        Ref<Shader> Get(const std::string& name);

        bool Exists(const std::string& name) const ;

    private:

        // value  is a ref of Shader
        std::unordered_map<std::string,Ref<Shader>> m_Shaders;
    };
}


#endif //SHADER_H
