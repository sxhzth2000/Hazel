//
// Created by tanhao on 2025/4/24.
//
#include "hzpch.h"
#include "OpenGLContext.h"


#include <Hazel/Core/Log.h>

#include "glad/glad.h"
#include "GLFW/glfw3.h"

namespace Hazle{
    OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
        :m_WindowHandle(windowHandle)
    {

    HZ_CORE_ASSERT(windowHandle,"windows handle is null!");
    }

    void OpenGLContext::Init()
    {
        glfwMakeContextCurrent(m_WindowHandle);
        int status=gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
        if (!status) {HZ_CORE_ERROR("fails to initialize Glad!");};

        const char* renderer = reinterpret_cast<const char*>(glGetString(GL_RENDERER));
         glGetString(GL_RENDERER);
        HZ_CORE_INFO("OpenGL Renderer {0}",renderer);
    }



    void OpenGLContext::SwapBuffers()
    {
        glfwSwapBuffers(m_WindowHandle);
    }

}
