//
// Created by tanhao on 2025/5/4.
//
#include "hzpch.h"

#include "OrthographicCamera.h"

#include "glm/gtc/matrix_transform.hpp"
namespace Hazel
{
    Hazel::OrthographicCamera::OrthographicCamera(float left, float right, float botton, float top)
        :m_ProjectionMatrix(glm::ortho(left,right,botton,top,-1.0f ,1.0f)),m_ViewMatrix(1.0f)
    {
        m_ViewProjectionMatrix=m_ProjectionMatrix * m_ViewMatrix ;
    }

    void OrthographicCamera::RecalculateViewMatrix()
    {
        glm::mat4 transform = glm::translate(glm::mat4(1.0),m_Postition)*
            glm::rotate(glm::mat4(1.0f),glm::radians( m_Rotation),glm::vec3(0,0,1));

        m_ViewMatrix=glm::inverse(transform);
        m_ViewProjectionMatrix=m_ProjectionMatrix * m_ViewMatrix ;

    }
}
