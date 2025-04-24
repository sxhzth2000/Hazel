//
// Created by tanhao on 2025/4/24.
//

#ifndef OPENGLCONTEXT_H
#define OPENGLCONTEXT_H
#include "Hazel/Renderer/GraphicsContext.h"

struct GLFWwindow;

namespace Hazle{

class OpenGLContext:public Hazel::GraphicsContext{

public:
    OpenGLContext(GLFWwindow* windowHandle);

    virtual void Init() override;
    virtual void SwapBuffers() override;
private:
    GLFWwindow* m_WindowHandle;

};


}
#endif //OPENGLCONTEXT_H
