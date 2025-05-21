//
// Created by tanhao on 2025/4/21.
//

#ifndef INPUT_H
#define INPUT_H
#include "hzpch.h"

#include "Hazel/Core/Core.h"
// 提供一个单例 static Input* s_Instance;
namespace Hazel{

    class  HAZEL_API Input
    {
    public:
       inline static bool IsKeyPressed(int keycode ) ;

        inline static bool IsMouseButtonPressed(int button);
        inline static float GetMouseX();
        inline static float GetMouseY();
        inline static std::pair<float,float> GetMousePosition();
    protected:
        virtual bool IsKeyPressedImp(int keycode)=0;
        virtual bool IsMouseButtonPressedImp(int button)=0;
        virtual float GetMouseXImp()=0;
        virtual float GetMouseYImp()=0;
        virtual std::pair<float,float> GetMousePositionImp()=0;

    public:
        static  Input* s_Instance;
    };



}

#endif //INPUT_H
