//
// Created by tanhao on 2025/4/17.
//

#ifndef LAYER_H
#define LAYER_H

#include "Hazel/Core/Core.h"
#include "Hazel/Events/Event.h"
namespace Hazel
{
    class HAZEL_API Layer {

    public:
        Layer(const std::string& name="Layer");
        virtual ~Layer();

        virtual void OnAttach(){}
        virtual void OnDetach(){}
        virtual void OnUpdate(){}
        virtual void OnEvent(Event& event) {}

        inline const std::string& GetName() const ;
    private:

        std::string m_DebugName;

    };
}
#endif //LAYER_H
