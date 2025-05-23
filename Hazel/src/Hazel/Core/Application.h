#pragma once


#include "Core.h"
#include "Hazel.h"
#include "Window.h"
#include "Hazel/Core/LayerStack.h"
#include <Hazel/Events/ApplicationEvent.h>
#include <Hazel/Imgui/ImGuiLayer.h>


namespace Hazel {


	class HAZEL_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		inline static Application& Get();
		inline Window& GetWindow();

	private:
		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);
		Scope <Window> m_Window;
		bool m_runing =true;
		bool m_Minimized = false;


		LayerStack m_LayerStack;
		ImGuiLayer* m_ImGuiLayer;
		float m_LastTime = 0.0f;

		int currentMode = 0;
		// 在渲染前根据选择设置 glViewport

	private:
		static Application* s_Instance;


	};


	//To be defined int CLIENT
	Application* CreateApplication();

}
