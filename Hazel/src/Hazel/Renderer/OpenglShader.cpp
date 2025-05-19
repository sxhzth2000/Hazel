    //
    // Created by tanhao on 2025/5/9.
    //

    #include "hzpch.h"
    #include "OpenglShader.h"

    #include <glad/glad.h>
    #include <glm/gtc/type_ptr.inl>





    Hazel::OpenglShader::OpenglShader(const std::string& filepath)
    {
        std::string source = ReadFile(filepath);
        auto ShaderSources = PreProcess(source);
        Compile(ShaderSources);

        // Texture.glsl
        //Extract name form filepath

        //查找最后一个“属于这个集合”的字符的位置。 一个字符串，包含字符 '/' 和 '\\' c++中 \ 为转义字符
        //这里为找到 / 或 \  unix 和 windows
        auto lastSlash = filepath.find_last_of("/\\");
        lastSlash = lastSlash == std::string::npos ? 0 : lastSlash+1;

        //如果lastSlash == std::string::npos。说明找不到路径分隔符。否则 就从最后一个斜杠之后的位置开始提取。
        auto lastDot = filepath.rfind('.');
        auto count = lastDot == std::string::npos ? filepath.size() - lastSlash : lastDot - lastSlash;
        m_Name = filepath.substr(lastSlash, count);


    }


    std::string Hazel::OpenglShader::ReadFile(const std::string& filepath)
    {
        std::string result;

        std::ifstream in(filepath,std::ios::in,std::ios::binary);
        if (in)
        {
            in.seekg(0,std::ios::end); //go to file end
            result.resize(in.tellg()); // pointer in the end.so file size equal  pointer size
            in.seekg(0,std::ios::beg);  //back to satrt

            in.seekg(0,std::ios::beg);
            in.read(&result[0],result.size()); // red  content by assign size

            in.close();
        }
        else
        {
            HZ_CORE_ERROR("Could not open file{0}",filepath);
        }

        return result;
    }

    std::unordered_map<GLenum, std::string> Hazel::OpenglShader::PreProcess(const std::string& source)
    {
        std::unordered_map<GLenum,std::string> shaderSources;

        const char* typeToken= "#type";
        size_t typeTokenLength = strlen(typeToken);
        size_t pos = source.find(typeToken,0);
        while (pos!= std::string::npos)
        {
            size_t eol = source.find_first_of("\r\n",pos);
            HZ_CORE_ASSERT(eol!=std::string::npos,"shader Syntax error");
            size_t begin = pos + typeTokenLength +1;
            std::string type = source.substr(begin,eol-begin);
            HZ_CORE_ASSERT(ShaderTypeFromString(type),"invalid shader type specifice");

            size_t nextLinePos = source.find_first_not_of("\r\n",eol);
            pos = source.find(typeToken,nextLinePos);
            shaderSources[ShaderTypeFromString(type)]=source.substr(nextLinePos,
                pos-(nextLinePos == std::string::npos ? source.size()-1 : nextLinePos));

        }

        return shaderSources;
    }






    void Hazel::OpenglShader::Compile(const std::unordered_map<GLenum, std::string>& shaderSources)
    {

        GLuint program = glCreateProgram();

        std::array<GLenum,2> glShaderIDs;
        int glShaderIDIndex = 0;

        for (auto& kv :shaderSources)
        {
            GLenum type = kv.first;
            const std::string& source = kv.second;

            // Create an empty vertex shader handle
            GLuint shader = glCreateShader(type);

            // Send the vertex shader source code to GL
            // Note that std::string's .c_str is NULL character terminated.
            const GLchar *sourceCStr = source.c_str();
            glShaderSource(shader, 1, &sourceCStr, 0);

            // Compile the vertex shader
            glCompileShader(shader);

            GLint isCompiled = 0;
            glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);


            if(isCompiled == GL_FALSE)
            {
                GLint maxLength = 0;
                glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

                // The maxLength includes the NULL character
                std::vector<GLchar> infoLog(maxLength);
                glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);

                // We don't need the shader anymore.
                glDeleteShader(shader);

                // Use the infoLog as you see fit.
                HZ_CORE_ERROR("{0}",infoLog.data());
                HZ_CORE_ASSERT(false,"Shader compilation failure!");

                // In this simple program, we'll just leave
                break;
            }

            glAttachShader(program, shader);
            glShaderIDs[glShaderIDIndex++]= shader;

        }
        m_RendererID=program;


        // Link our program
        glLinkProgram(program);

        // Note the different functions here: glGetProgram* instead of glGetShader*.
        GLint isLinked = 0;
        glGetProgramiv(program, GL_LINK_STATUS, (int *)&isLinked);
        if (isLinked == GL_FALSE)
        {
        GLint maxLength = 0;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

        // The maxLength includes the NULL character
        std::vector<GLchar> infoLog(maxLength);
        glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

        HZ_CORE_ERROR("{0}",infoLog.data());
        HZ_CORE_ASSERT(false,"Shader link  failure!");

        // We don't need the program anymore.
        glDeleteProgram(program);
        // Don't leak shaders either.

            for (auto id :glShaderIDs)
            {
                glDeleteShader(id);
            }
        // Use the infoLog as you see fit.

        // In this simple program, we'll just leave
        return;
        }

        // Always detach shaders after a successful link.

        for (auto id :glShaderIDs)
        {
            glDetachShader(program, id);
        }
    }

    GLenum Hazel::OpenglShader::ShaderTypeFromString(const std::string& type)
    {
        if (type== "vertex")
            return GL_VERTEX_SHADER;
        if (type== "fragment"|| type== "pixel")
            return GL_FRAGMENT_SHADER;

        HZ_CORE_ASSERT(false,"Unknow shader type!");
        return 0;
    }

    Hazel::OpenglShader::OpenglShader(const std::string name,const std::string& vertexSrc, const std::string fragmentSrc)
    {

        std::unordered_map<GLenum,std::string> sources;

        sources[GL_VERTEX_SHADER]   = vertexSrc;
        sources[GL_FRAGMENT_SHADER] = fragmentSrc;
        Compile(sources);
    }

    Hazel::OpenglShader::~OpenglShader()
    {
        glDeleteProgram(m_RendererID);
    }

    void Hazel::OpenglShader::Bind() const
    {
        glUseProgram(m_RendererID);
    }

    void Hazel::OpenglShader::Unbind() const
    {
        glUseProgram(0);
    }

    void Hazel::OpenglShader::UploadUniformInt(const std::string& name, const unsigned value)
    {
        GLint location = glGetUniformLocation(m_RendererID,name.c_str());
        glUniform1ui(location,value);
    }


    void Hazel::OpenglShader::UploadUniformFloat1(const std::string& name, const float value)
    {
        GLint location = glGetUniformLocation(m_RendererID,name.c_str());
        glUniform1f(location,value);
    }

    void Hazel::OpenglShader::UploadUniformFloat2(const std::string& name, const glm::vec2& value)
    {
        GLint location = glGetUniformLocation(m_RendererID,name.c_str());
        glUniform2f(location,value.x,value.y);
    }

    void Hazel::OpenglShader::UploadUniformFloat3(const std::string& name, const glm::vec3& value)
    {
        GLint location = glGetUniformLocation(m_RendererID,name.c_str());
        glUniform3f(location,value.x,value.y,value.z);
    }
    void Hazel::OpenglShader::UploadUniformFloat4(const std::string& name, const glm::vec4& value)
    {
        GLint location = glGetUniformLocation(m_RendererID,name.c_str());
        glUniform4f(location,value.x,value.y,value.z,value.w);
    }


    void Hazel::OpenglShader::UploadUniformMat3(const std::string& name, const glm::mat3& matrix)
    {
        GLint location = glGetUniformLocation(m_RendererID,name.c_str());
        glUniformMatrix3fv(location,1,GL_FALSE,glm::value_ptr(matrix));
    }

    void Hazel::OpenglShader::UploadUniformMat4(const std::string& name, const glm::mat4& matrix)
    {
        GLint location = glGetUniformLocation(m_RendererID,name.c_str());
        glUniformMatrix4fv(location,1,GL_FALSE,glm::value_ptr(matrix));
    }






