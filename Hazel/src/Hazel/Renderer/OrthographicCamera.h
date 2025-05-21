//
// Created by tanhao on 2025/5/4.
//

#ifndef ORTHOGRAPHICCAMERA_H
#define ORTHOGRAPHICCAMERA_H
#include <glm/glm.hpp>

namespace Hazel
{
    class HAZEL_API OrthographicCamera
    {
    public:
        OrthographicCamera(float left, float right , float botton, float top);

        void SetProjection(float left, float right , float botton, float top );



        const glm::vec3 & GetPosition() const {return m_Postition;}
        void SetPosition(const glm::vec3& position) {m_Postition=position ; RecalculateViewMatrix();}

        float GetRotation() const {return m_Rotation;}
        void SetRotation(float rotation) { m_Rotation = rotation ; RecalculateViewMatrix();}


        const glm::mat4& GetProjectionMatrix() const {return m_ProjectionMatrix;}
        const glm::mat4& GetViewMatrix() const {return m_ViewMatrix;}
        const glm::mat4& GetViewProjectionMatrix() const {return m_ViewProjectionMatrix;}

    private:
        void RecalculateViewMatrix();


    private:
        glm::mat4 m_ProjectionMatrix;
        glm::mat4 m_ViewMatrix;
        glm::mat4 m_ViewProjectionMatrix;
        glm::vec3 m_Postition={0.0f,0.0f,0.0f};
        float m_Rotation=0.0f ;

    };
}


#endif //ORTHOGRAPHICCAMERA_H
