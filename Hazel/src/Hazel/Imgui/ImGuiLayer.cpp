//
// Created by tanhao on 2025/4/18.
//
#include "hzpch.h"
#include "ImGuiLayer.h"

#include <Hazel/Core/Log.h>

#include "imgui.h"
#include "imgui_impl_opengl3.h"
#include "imgui_impl_glfw.h"


#include "glad/glad.h"
//#include "GLFW/glfw3.h"
#include "GLFW/glfw3.h"
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

        ImGuiIO& io = ImGui::GetIO();
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            GLFWwindow* backup_current_context = glfwGetCurrentContext();
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            glfwMakeContextCurrent(backup_current_context);
        }


    }


    void ImGuiLayer::OnEvent(Event& event)
    {
        EventDispatcher dispatcher(event);
        dispatcher.Dispatch<MouseButtonPressedEvent>(HZ_BIND_EVENT_FN(ImGuiLayer::OnMouseButtonPressedEvent));
        dispatcher.Dispatch<MouseButtonReleasedEvent>(HZ_BIND_EVENT_FN(ImGuiLayer::OnMouseButtonReleasedEvent));
        dispatcher.Dispatch<MouseMovedEvent>(HZ_BIND_EVENT_FN(ImGuiLayer::OnMouseMovedEvent));
        dispatcher.Dispatch<MouseScrolledEvent>(HZ_BIND_EVENT_FN(ImGuiLayer::OnMouseScrolledEvent));
        dispatcher.Dispatch<KeyPressedEvent>(HZ_BIND_EVENT_FN(ImGuiLayer::OnKeyPressedEvent));
        dispatcher.Dispatch<KeyTypeEvent>(HZ_BIND_EVENT_FN(ImGuiLayer::OnkeyTypeEvent));
        dispatcher.Dispatch<KeyReleasedEvent>(HZ_BIND_EVENT_FN(ImGuiLayer::OnKeyReleasedEvent));
        dispatcher.Dispatch<WindowResizeEvent>(HZ_BIND_EVENT_FN(ImGuiLayer::OnWindowResizeEvent));
    }
    void ImGuiLayer::OnAttach()
    {
        HZ_CORE_ERROR("imgui on attach");
        ImGui::CreateContext();


         ImGuiIO& io = ImGui::GetIO(); (void)io;

        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // Enable Docking
        io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;       // Enable Multi-Viewport / Platform Windows

        io.BackendFlags  |= ImGuiBackendFlags_HasMouseCursors;  //支持 ImGui 控制鼠标样式
        io.BackendFlags  |= ImGuiBackendFlags_HasSetMousePos;  //支持 ImGui 设置鼠标位置



        ImGui::StyleColorsDark();

        Application& app = Application::Get();
        auto window = static_cast<GLFWwindow*>(app.GetWindow().GetNativeWindow());
        std::cout << "GLFW window ptr: " << window << std::endl;

        ImGui_ImplGlfw_InitForOpenGL(window, false);//是否启用imgui的回调函数，按键，移动等
        ImGui_ImplOpenGL3_Init("#version 430 core");
    }


    void ImGuiLayer::OnDetach()
    {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }

    bool ImGuiLayer::OnMouseButtonPressedEvent(MouseButtonPressedEvent& e)
    {
        ImGuiIO& io=ImGui::GetIO();
        io.MouseDown[e.GetMouseButton()]=true;
        return false;
    }

    bool ImGuiLayer::OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e)
    {

        ImGuiIO& io=ImGui::GetIO();  //io是一个结构体，存
        io.MouseDown[e.GetMouseButton()]=false;
        return false;
    }



    bool ImGuiLayer::OnMouseMovedEvent(MouseMovedEvent& e)
    {
        ImGuiIO& io=ImGui::GetIO();
        io.MousePos=ImVec2(e.GetX(),e.GetY());
        return false;
    }

    bool ImGuiLayer::OnMouseScrolledEvent(MouseScrolledEvent& e)
    {
        ImGuiIO& io=ImGui::GetIO();
        io.MouseWheel+=e.GetXOffset();
        io.MouseWheelH+=e.GetYOffset();

        return false;
    }

    bool ImGuiLayer::OnKeyPressedEvent(KeyPressedEvent& e)
    {
        ImGuiIO& io = ImGui::GetIO();

        // 将 GLFW 键值映射到 ImGuiKey
        ImGuiKey imguiKey = ImGui_ImplGlfw_KeyToImGuiKey(e.GetKeyCode(), 0);  // 第二个参数为 scancode，但未使用

        io.AddKeyEvent(imguiKey, true);  // 标记按下

        // 处理修饰键状态
        io.AddKeyEvent(ImGuiKey_ModCtrl, io.KeyCtrl);    // 通过 io.KeyCtrl 来检查 Ctrl 键状态
        io.AddKeyEvent(ImGuiKey_ModShift, io.KeyShift);  // 通过 io.KeyShift 来检查 Shift 键状态
        io.AddKeyEvent(ImGuiKey_ModAlt, io.KeyAlt);      // 通过 io.KeyAlt 来检查 Alt 键状态
        io.AddKeyEvent(ImGuiKey_ModSuper, io.KeySuper);  // 通过 io.KeySuper 来检查 Super 键状态

        return false;
    }

    bool ImGuiLayer::OnKeyReleasedEvent(KeyReleasedEvent& e)
    {
        ImGuiIO& io = ImGui::GetIO();

        ImGuiKey imguiKey = ImGui_ImplGlfw_KeyToImGuiKey(e.GetKeyCode(), 0);

        io.AddKeyEvent(imguiKey, false);  // 标记松开

        // 更新修饰键状态（因为可能也松开了）
        io.AddKeyEvent(ImGuiKey_ModCtrl, io.KeyCtrl);    // 使用 io.KeyCtrl 判断 Ctrl 键状态
        io.AddKeyEvent(ImGuiKey_ModShift, io.KeyShift);  // 使用 io.KeyShift 判断 Shift 键状态
        io.AddKeyEvent(ImGuiKey_ModAlt, io.KeyAlt);      // 使用 io.KeyAlt 判断 Alt 键状态
        io.AddKeyEvent(ImGuiKey_ModSuper, io.KeySuper);  // 使用 io.KeySuper 判断 Super 键状态

        return false;
    }

       bool ImGuiLayer::OnkeyTypeEvent(KeyTypeEvent& e)
       {
        ImGuiIO& io=ImGui::GetIO();
        int keycode = e.GetKeyCode();
        io.AddInputCharacter((unsigned short) keycode);

           return false;
       }


    bool ImGuiLayer::OnWindowResizeEvent(WindowResizeEvent& e)
    {
        ImGuiIO& io=ImGui::GetIO();
        io.DisplaySize=ImVec2(e.GetWidth(),e.GetHeight());
        io.DisplayFramebufferScale=ImVec2(1.0f,1.0f);
        glViewport(0,0,e.GetWidth(),e.GetHeight());
        return false;
    }
}
