//
// Created by tanhao on 2025/5/21.
//
#include "hzpch.h"
#include "OrthographicCameraController.h"

#include "input.h"
#include "KeyCodes.h"

Hazel::OrthographicCameraController::OrthographicCameraController(float aspectRatio,bool rotation):
m_AspectRatio(aspectRatio),m_Camera(-m_AspectRatio*m_ZoomLevel,m_AspectRatio* m_ZoomLevel , -m_ZoomLevel,m_ZoomLevel),m_Rotation(rotation)
{
}

void Hazel::OrthographicCameraController::OnUpdate(TimeStep ts)
{

    //HZ_TRACE("TimeStep: {0}s ({1}ms {2})",ts.GetSeconds(),ts.GetMilliseconds(), float(ts));


        if (Input::IsKeyPressed(HZ_KEY_A))
        {
            m_CameraPosition.x-= m_CameraTranslationSpeed*ts;
        }
        if (Hazel::Input::IsKeyPressed(HZ_KEY_D))
        {
            m_CameraPosition.x+= m_CameraTranslationSpeed*ts;
        }
        if (Input::IsKeyPressed(HZ_KEY_W))
        {
            m_CameraPosition.y+= m_CameraTranslationSpeed*ts;
        }
        if (Input::IsKeyPressed(HZ_KEY_S))
        {
            m_CameraPosition.y-= m_CameraTranslationSpeed*ts;
        }
    if(m_Rotation)
    {
        if (Input::IsKeyPressed(HZ_KEY_Q))
        {
            m_CameraRotation-= m_CameraRotationSpeed*ts;
        }

        if (Input::IsKeyPressed(HZ_KEY_E))
        {
            m_CameraRotation+= m_CameraRotationSpeed*ts;
        }

        m_Camera.SetRotation(m_CameraRotation);
    }

    m_Camera.SetPosition(m_CameraPosition);

}

void Hazel::OrthographicCameraController::OnEvent(Event& e)
{
    EventDispatcher dispatcher(e);
    dispatcher.Dispatch<MouseScrolledEvent>(HZ_BIND_EVENT_FN(OrthographicCameraController::OnMouseScrolled));
    dispatcher.Dispatch<WindowResizeEvent>(HZ_BIND_EVENT_FN(OrthographicCameraController::OnWindowResized));
}

bool Hazel::OrthographicCameraController::OnMouseScrolled(MouseScrolledEvent& e)
{
    float yOffset = e.GetYOffset();

    float zoomChange = yOffset * m_ZoomLevel * 0.1f; // 缩放随距离动态变化
    m_ZoomLevel -= zoomChange;
    m_ZoomLevel = std::clamp(m_ZoomLevel, 0.05f, 10.0f);

   // HZ_TRACE("Mouse scroll Zoom Level: {0}, zoomChange: {1}", m_ZoomLevel, zoomChange);

    m_Camera.SetProjection(
        -m_AspectRatio * m_ZoomLevel,
         m_AspectRatio * m_ZoomLevel,
        -m_ZoomLevel,
         m_ZoomLevel
    );

    return false;
}




bool Hazel::OrthographicCameraController::OnWindowResized(WindowResizeEvent& e)
{
    m_AspectRatio = (float)e.GetWidth() / (float)e.GetHeight();

    return false;
}
