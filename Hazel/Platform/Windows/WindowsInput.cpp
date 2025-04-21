//
// Created by tanhao on 2025/4/21.
//

#include "WindowsInput.h"


#include <GLFW/glfw3.h>
#include <Hazel/Core/Application.h>

namespace Hazel {

    Input*  Input::s_Instance= new WindowsInput();

    bool WindowsInput::IsKeyPressedImp(int keycode)
    {
        auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
        auto state=glfwGetKey(window,keycode);

        return state==GLFW_PRESS || state == GLFW_REPEAT;
    }

    bool WindowsInput::IsMouseButtonPressedImp(int button)
    {
        auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
        auto state=glfwGetMouseButton(window,button);
        return state==GLFW_PRESS;
    }

    std::pair<float,float> WindowsInput::GetMousePositionImp()
    {
        auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
        double xpos,ypos;
        glfwGetCursorPos(window,&xpos,&ypos);

        return {(float)xpos,(float)ypos};
    }

    float WindowsInput::GetMouseXImp( )
    {
        auto[x,y]=GetMousePositionImp();
        return x;
    }

    float WindowsInput::GetMouseYImp( )
    {
        auto[x,y]=GetMousePositionImp();
        return y;
    }


} // Hazel