//
// Created by tanhao on 2025/4/16.
//

#include "hzpch.h"
#include "WindowsWindow.h"

#include <Hazel/Core/Log.h>

namespace Hazel{

    static bool s_GLFEInitialized =false;

    Window* Window::Create(const WindowProps& props)
    {
        return new WindowsWindow(props);

    }

    WindowsWindow::WindowsWindow(const WindowProps& props)
    {
        Init(props);
    }


    WindowsWindow::~WindowsWindow()
    {
        Shutdown();
    }

    void WindowsWindow::OnUpdate()
    {
        glfwPollEvents();
        glfwSwapBuffers(m_Window);
    }

    void WindowsWindow::SetVSync(bool enabled)
    {
        if(enabled)
            glfwSwapInterval(1);
        else
            glfwSwapInterval(0);

        m_Data.VSync= enabled;
    }

    void WindowsWindow::IsVSync() const
    {
    }

    void WindowsWindow::Init(const WindowProps& props)
    {
        m_Data.Tiele=props.Title;
        m_Data.Height=props.Height;
        m_Data.Width=props.Width;

        HZ_CORE_INFO("Creating windows: {0} ({1}, {2})",props.Title,props.Width,props.Height);

        if(!s_GLFEInitialized)
        {
            //TODO::glfwTerminate on system shutdown

            int success =glfwInit();
            if (!success)
            HZ_CORE_INFO(std::to_string(success),"Could not intialize GLFW!");
            s_GLFEInitialized=true;

        }

        m_Window=glfwCreateWindow((int)props.Width,(int) props.Height,m_Data.Tiele.c_str(),nullptr,nullptr);
        glfwMakeContextCurrent(m_Window);
        glfwSetWindowUserPointer(m_Window,&m_Data);
        SetVSync(true);
    }

    void WindowsWindow::Shutdown()
    {
        glfwDestroyWindow(m_Window);
    }
}
