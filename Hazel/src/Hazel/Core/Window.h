//
// Created by tanhao on 2025/4/16.
//

#ifndef WINDOW_H
#define WINDOW_H

#include "hzpch.h"

#include "Hazel/Core/Core.h"
#include "Hazel/Events/Event.h"

namespace Hazel {

    struct WindowProps
    {
        std::string Title;
        unsigned int Width;
        unsigned int Height;

        WindowProps(const std::string& title = "Hazel Engine",
                    unsigned int width = 1280,
                    unsigned int height = 720)
                        :Title(title),Width(width),Height(height)
        {

        }


    };

    //Inter face representing a desktop system based Window
    class HAZEL_API Window
    {
    public:
        using EventCallbackFn = std::function<void(Event&)>;

        virtual ~Window(){}

        virtual void OnUpdate()=0;

        virtual unsigned int GetWidth() const=0;
        virtual unsigned int GetHeight() const=0;

        //Window attributes
        virtual void SetEventCallback(const EventCallbackFn& callback)=0;
        virtual void SetVSync(bool enabled)=0;
        virtual void IsVSync()const=0;
        // 加上这个函数声明 👇
        virtual void* GetNativeWindow() const = 0;

        static Window* Create(const WindowProps& props = WindowProps());
    };
}







#endif //WINDOW_H
