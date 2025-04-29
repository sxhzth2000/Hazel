#pragma once


#include "Core.h"
#include "Window.h"
#include "Hazel/LayerStack.h"
#include <Hazel/Events/ApplicationEvent.h>
#include <Hazel/Imgui/ImGuiLayer.h>

#include "Hazel/Buffer.h"
#include "OpenGL/OpenglBuffer.h"
#include "Hazel/Renderer/Shader.h"

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
		std::unique_ptr<Window> m_Window;
		bool m_runing =true;
		LayerStack m_LayerStack;
		ImGuiLayer* m_ImGuiLayer;

		unsigned int m_VertexArraay;
	private:
		static Application* s_Instance;
		std::unique_ptr<Shader>  m_Shader;
		std::unique_ptr<VertexBuffer> m_VertexBuffer;
		std::unique_ptr<IndexBuffer> m_IndexBuffer;
	};


	//To be defined int CLIENT
	Application* CreateApplication();

}
