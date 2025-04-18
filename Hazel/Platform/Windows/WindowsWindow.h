//
// Created by tanhao on 2025/4/16.
//

#ifndef WINDOWSWINDOW_H
#define WINDOWSWINDOW_H

#include "hzpch.h"






#include "glad/glad.h"
#include <GLFW/glfw3.h>

#include "Window.h"

namespace Hazel{

class WindowsWindow : public Window
{
public:
    WindowsWindow(const WindowProps& props);
    virtual ~WindowsWindow();

    void OnUpdate() override;
    inline unsigned int GetWidth() const override{return m_Data.Width;};
    inline unsigned int GetHeight() const override{return m_Data.Height;};

    //Windw attributes
    inline void SetEventCallback(const EventCallbackFn& callback) override {m_Data.EventCallback=callback;} ;
    void SetVSync(bool enabled) override;
    void IsVSync()const override;
    virtual void* GetNativeWindow() const override;

private:
    virtual void Init(const WindowProps& props);
    virtual void Shutdown();


private:
    GLFWwindow* m_Window;

    struct WindowData
    {
        std::string Tiele;
        unsigned int Width,Height;
        bool VSync;

        EventCallbackFn EventCallback;

    };

    WindowData m_Data;
};

}



#endif //WINDOWSWINDOW_H
