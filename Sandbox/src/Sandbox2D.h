//
// Created by tanhao on 2025/5/22.
//

#ifndef SANDBOX2D_H
#define SANDBOX2D_H
#include "../../Hazel/src/Hazel/Core/Layer.h"

#include "Hazel.h"

class Sandbox2D : public  Hazel::Layer{


public:
    Sandbox2D();
    virtual ~Sandbox2D()  = default;

    virtual void OnAttach()override;
    virtual void OnDetach()override;
    void OnUpdate(Hazel::TimeStep ts) override;

    void OnImguiRender() override;

    void OnEvent(Hazel::Event& e)override;
private:
    Hazel::OrthographicCameraController m_Camera_Controller;


    //Temp
    glm::vec4 color={0.0,0.0,0.0,1};
    Hazel::Ref<Hazel::VertexArray>  m_SquareArray;
    Hazel::Ref <Hazel::Shader>      m_FlatColorShader;

    glm::vec4 m_SquareColor= {0.8f,0.2f,0.3f, 1.0f};
};



#endif //SANDBOX2D_H
