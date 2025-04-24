//
// Created by tanhao on 2025/4/18.
//

#ifndef IMGUILAYER_H
#define IMGUILAYER_H


#include <Hazel/Events/ApplicationEvent.h>

#include "Hazel/Core/Core.h"


#include <Hazel/Events/MouseEvent.h>
#include <Hazel/Events/KeyEvent.h>

#include "Hazel/Layer.h"


namespace Hazel{
    class HAZEL_API ImGuiLayer: public Layer
    {
    public:
        ImGuiLayer();
        ~ImGuiLayer();

        void OnEvent(Event& event);
        void Begin();
        void End();

        void OnAttach();
        void OnDetach();
    private:
        bool OnMouseButtonPressedEvent(MouseButtonPressedEvent& e);
        bool OnMouseButtonReleasedEvent (MouseButtonReleasedEvent& e);
        bool OnMouseMovedEvent(MouseMovedEvent& e);
        bool OnMouseScrolledEvent(MouseScrolledEvent& e);


        bool OnKeyPressedEvent(KeyPressedEvent& e);
        bool OnKeyReleasedEvent(KeyReleasedEvent& e);
        bool OnkeyTypeEvent(KeyTypeEvent& e);
        bool OnWindowResizeEvent(WindowResizeEvent& e);

    };
}


#endif //IMGUILAYER_H

