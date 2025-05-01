#pragma once


#include "Core.h"
#include "Window.h"
#include "Hazel/LayerStack.h"
#include <Hazel/Events/ApplicationEvent.h>
#include <Hazel/Imgui/ImGuiLayer.h>

#include "../Renderer/Buffer.h"
#include "OpenGL/OpenglBuffer.h"
#include "Hazel/Renderer/Shader.h"
#include "Hazel/Renderer/VertexArray.h"

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


	private:
		static Application* s_Instance;
		std::shared_ptr<Shader>  m_Shader;
		std::shared_ptr<VertexArray> m_VertexArray;
		std::shared_ptr<VertexBuffer> m_VertexBuffer;
		std::shared_ptr<IndexBuffer> m_IndexBuffer;

		std::shared_ptr<Shader>  m_Shader_Square;
		std::shared_ptr<VertexArray> m_SquareVA;
		std::shared_ptr<VertexBuffer> m_SquareVB;
		std::shared_ptr<IndexBuffer> m_SquareIB;
	};


	//To be defined int CLIENT
	Application* CreateApplication();

}
