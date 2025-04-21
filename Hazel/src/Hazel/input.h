//
// Created by tanhao on 2025/4/21.
//

#ifndef INPUT_H
#define INPUT_H

#include "Hazel/Core/Core.h"
// 提供一个单例 static Input* s_Instance;
namespace Hazel{

    class HAZEL_API Input
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




    private:
        static Input* s_Instance;
    };

    inline bool Input::IsKeyPressed(int keycode)
    {
        return s_Instance->IsKeyPressedImp(keycode);
    }

    inline bool Input::IsMouseButtonPressed(int button)
    {
        return s_Instance->IsMouseButtonPressedImp(button);
    }

    inline float Input::GetMouseX()
    {
        return s_Instance->GetMouseXImp();

    }

    inline float Input::GetMouseY()
    {
        return s_Instance->GetMouseYImp();
    }

    inline std::pair<float,float> Input::GetMousePosition()
    {
        return s_Instance->GetMousePositionImp();
    }
}





#endif //INPUT_H
