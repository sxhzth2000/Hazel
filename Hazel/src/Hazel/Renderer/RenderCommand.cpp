
//
// Created by tanhao on 2025/5/1.
//
#include "hzpch.h"

#include "RenderCommand.h"
#include "OpenGL/OpenGLRendererAPI.h"

namespace Hazel
{
    RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI;

}