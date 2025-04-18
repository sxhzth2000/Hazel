//
// Created by tanhao on 2025/4/18.
//
#include "hzpch.h"
#include "ImGuiLayer.h"

#include <Hazel/Core/Log.h>

#include "imgui.h"
#include "imgui_impl_opengl3.h"
#include "imgui_impl_glfw.h"

#include "Hazel/Core/Application.h"

namespace Hazel{
    ImGuiLayer::ImGuiLayer()
        :Layer("ImGuiLayer")
    {
    }

    ImGuiLayer::~ImGuiLayer()
    {
    }
    void ImGuiLayer::OnUpdate()
    {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();

        ImGui::NewFrame();

        static bool show = true;
        ImGui::ShowDemoWindow(&show);
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }


    void ImGuiLayer::OnEvent(Event& event)
    {

    }
    void ImGuiLayer::OnAttach()
    {
        HZ_CORE_ERROR("imgui on attach");
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
        ImGui::StyleColorsDark();

        Application& app = Application::Get();
        auto window = static_cast<GLFWwindow*>(app.GetWindow().GetNativeWindow());
        std::cout << "GLFW window ptr: " << window << std::endl;

        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui_ImplOpenGL3_Init("#version 430 core");
    }


    void ImGuiLayer::OnDetach()
    {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }
}
