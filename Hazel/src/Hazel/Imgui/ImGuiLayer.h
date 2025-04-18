//
// Created by tanhao on 2025/4/18.
//

#ifndef IMGUILAYER_H
#define IMGUILAYER_H

#include "Hazel/Core/Core.h"
#include "Hazel/Layer.h"

namespace Hazel{
    class HAZEL_API ImGuiLayer: public Layer
    {
    public:
        ImGuiLayer();
        ~ImGuiLayer();
        void OnUpdate() ;
        void OnEvent(Event& event);
        void OnAttach();
        void OnDetach();
    };
}


#endif //IMGUILAYER_H

