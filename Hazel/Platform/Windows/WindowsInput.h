//
// Created by tanhao on 2025/4/21.
//

#ifndef WINDOWSINPUT_H
#define WINDOWSINPUT_H
#include "Hazel/Core/input.h"

namespace Hazel {

class HAZEL_API WindowsInput : public Input{



protected:
    virtual bool IsKeyPressedImp(int keycode) override;
    virtual bool IsMouseButtonPressedImp(int button)override;
    virtual float GetMouseXImp( )override;
    virtual float GetMouseYImp( )override;
    virtual std::pair<float,float> GetMousePositionImp() override;
};

} // Hazel

#endif //WINDOWSINPUT_H
