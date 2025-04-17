//
// Created by tanhao on 2025/4/17.
//

#include "Layer.h"

Hazel::Layer::Layer(const std::string& name)
{
}

Hazel::Layer::~Layer()
{
}

const std::string& Hazel::Layer::GetName() const
{
    {return m_DebugName;}
}
