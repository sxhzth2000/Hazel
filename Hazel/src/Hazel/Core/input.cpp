#include "Input.h"

namespace Hazel {

    Input* Input::s_Instance = nullptr;



    bool Input::IsKeyPressed(int keycode) {
        return s_Instance->IsKeyPressedImp(keycode);
    }

    bool Input::IsMouseButtonPressed(int button) {
        return s_Instance->IsMouseButtonPressedImp(button);
    }

    float Input::GetMouseX() {
        return s_Instance->GetMouseXImp();
    }

    float Input::GetMouseY() {
        return s_Instance->GetMouseYImp();
    }

    std::pair<float, float> Input::GetMousePosition() {
        return s_Instance->GetMousePositionImp();
    }

} // namespace Hazel
