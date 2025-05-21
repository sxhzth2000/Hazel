//
// Created by tanhao on 2025/4/16.
//

#include "hzpch.h"
#include "WindowsWindow.h"



#include <Hazel/Core/Log.h>
#include <Hazel/Events/ApplicationEvent.h>
#include "Hazel/Events/KeyEvent.h"
#include "Hazel/Events/MouseEvent.h"
#include "OpenGL/OpenGLContext.h"

namespace Hazel{

    static bool s_GLFEInitialized =false;
    static void GLFWErrorCallback(int error_code, const char* description)
    {
        HZ_CORE_ERROR("GLFW Error ({0}):{1}",error_code,description);
    }
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



    void WindowsWindow::Init(const WindowProps& props)
    {
        m_Data.Title=props.Title;
        m_Data.Height=props.Height;
        m_Data.Width=props.Width;

        HZ_CORE_INFO("Creating windows: {0} ({1}, {2})",props.Title,props.Width,props.Height);

        if(!s_GLFEInitialized)
        {
            //TODO::glfwTerminate on system shutdown
            int success =glfwInit();
            if (!success)
            HZ_CORE_INFO(std::to_string(success),"Could not intialize GLFW!");
            glfwSetErrorCallback(GLFWErrorCallback);
            s_GLFEInitialized=true;

        }

        m_Window=glfwCreateWindow((int)props.Width,(int) props.Height,m_Data.Title.c_str(),nullptr,nullptr);
        m_Context=new Hazle::OpenGLContext(m_Window);
        m_Context->Init();

        glfwSetWindowUserPointer(m_Window,&m_Data);
        SetVSync(true);

        /*//Set GLFW callbacks
        glfwSetWindowSizeCallback(m_Window,[](GLFWwindow* window,int width,int height)
        {
             WindowData& data = * (WindowData* ) glfwGetWindowUserPointer(window);
            data.Width = width;
            data.Height = height;

            WindowResizeEvent event(width,height);
            data.EventCallback(event);
           });*/

        glfwSetWindowCloseCallback(m_Window,[](GLFWwindow* window)
        {
            WindowData& data = * (WindowData* ) glfwGetWindowUserPointer(window);
            WindowCloseEvent event;
            data.EventCallback(event);
        });

        glfwSetKeyCallback(m_Window,[](GLFWwindow* window,int key,int scancode,int action,int mods)
        {
            WindowData& data = * (WindowData* ) glfwGetWindowUserPointer(window);

            switch (action)
            {
                case GLFW_PRESS:
                {
                    KeyPressedEvent event(key,0);
                    data.EventCallback(event);
                    break;
                }
                case GLFW_RELEASE:
                {
                    KeyReleasedEvent event(key);
                    data.EventCallback(event);
                    break;
                }
                case GLFW_REPEAT:
                {
                    KeyPressedEvent event(key,1);
                    data.EventCallback(event);
                    break;
                }
            }
        });


        glfwSetCharCallback(m_Window,[](GLFWwindow* window, unsigned int keycode)
        {
            WindowData& data = * (WindowData* ) glfwGetWindowUserPointer(window);
            KeyTypedEvent event(keycode);
            data.EventCallback(event);
        });


        glfwSetMouseButtonCallback(m_Window,[](GLFWwindow* window, int button, int action, int mods)
        {
            WindowData& data = * (WindowData* ) glfwGetWindowUserPointer(window);

            switch (action)
            {
                case GLFW_RELEASE:
                {
                    MouseButtonReleasedEvent event(button);
                    data.EventCallback(event);
                    break;
                }
            case GLFW_PRESS:
                {
                    MouseButtonPressedEvent event(button);
                    data.EventCallback(event);
                    break;
                }
            }
        });

        glfwSetScrollCallback(m_Window,[](GLFWwindow* window, double xoffset, double yoffset)
        {
            WindowData& data = * (WindowData* ) glfwGetWindowUserPointer(window);

            MouseScrolledEvent event((float) xoffset,(float)yoffset);
            data.EventCallback(event);
        });

        glfwSetCursorPosCallback(m_Window,[](GLFWwindow* window, double xpos, double ypos)
        {
            WindowData& data = * (WindowData* ) glfwGetWindowUserPointer(window);

            MouseMovedEvent event((float)xpos,(float)ypos);
            data.EventCallback(event);
        });
    }

    void WindowsWindow::Shutdown()
    {
        glfwDestroyWindow(m_Window);
    }
    void WindowsWindow::OnUpdate()
    {
        glfwPollEvents();
        m_Context->SwapBuffers();
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

    void* WindowsWindow::GetNativeWindow() const
    {
        return m_Window;
    }
}
