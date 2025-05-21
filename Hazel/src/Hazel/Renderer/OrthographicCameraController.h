//
// Created by tanhao on 2025/5/21.
//

#ifndef ORTHOGRAPHICCAMERACONTROLLER_H
#define ORTHOGRAPHICCAMERACONTROLLER_H


#include "Hazel/Core/TimeStep.h"
#include "Hazel/Events/ApplicationEvent.h"
#include "Hazel/Events/Event.h"
#include "Hazel/Events/MouseEvent.h"
#include "Hazel/Renderer/OrthographicCamera.h"


namespace Hazel
{
    class HAZEL_API OrthographicCameraController {

    public:
        OrthographicCameraController( float aspectRatio ,bool rotation = false);

        void OnUpdate(TimeStep ts);
        void OnEvent(Event& e);

        OrthographicCamera& GetCamera() {return m_Camera;}

       const  OrthographicCamera& GetCamera() const {return m_Camera;}

    private:
        bool OnMouseScrolled(MouseScrolledEvent& e);
        bool OnWindowResized(WindowResizeEvent& e);

    public:

    private:
        float m_AspectRatio;
        float m_ZoomLevel = 1.0f;
        OrthographicCamera m_Camera;
        bool m_Rotation =false;

        glm::vec3 m_CameraPosition = {0.0f, 0.0f ,0.0f };

        float m_CameraTranslationSpeed = 1.0f , m_CameraRotationSpeed = 90.0f;
        float m_CameraRotation= 0.0f;
    };
}

#endif //ORTHOGRAPHICCAMERACONTROLLER_H
