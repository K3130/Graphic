#pragma once

#include "common.h"

namespace Graphic
{   
	template <typename Derived>
	class ImGuiWindowOpengl	{
	public:
		ImGuiWindowOpengl() : m_window(nullptr) {} 
		~ImGuiWindowOpengl() {}
	
		void Init(int aWidth, int aHeight, const char* aTitle)
		{
			//-------------------------------------------
			// Setup window
			if (!glfwInit())
			{
				std::cerr << "Failed to initialize GLFW" << std::endl;
			}

			const char* glsl_version = "#version 150";
			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
			glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
			glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // 3.0+ only
			glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
			m_window = glfwCreateWindow(aWidth, aHeight, aTitle, NULL, NULL);
			if (m_window == NULL)
			{
				std::cerr << "Failed to create window" << std::endl;
			}

			glfwMakeContextCurrent(m_window);
			glfwSwapInterval(1); // Enable vsync

			if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
			{
				std::cerr << "Unable to context to OpenGL";
			}
			//-------------------------------------------
			IMGUI_CHECKVERSION();
			ImGui::CreateContext();
			ImGuiIO& io = ImGui::GetIO();
			// Setup Platform/Renderer bindings
			ImGui_ImplGlfw_InitForOpenGL(m_window, true);
			ImGui_ImplOpenGL3_Init(glsl_version);
			ImGui::StyleColorsDark();
			//-------------------------------------------
			//Start
			while (!glfwWindowShouldClose(m_window))
			{
				glfwPollEvents();
				NewFrame();
				UpdateGraphicScene();
				Render();
				glfwSwapBuffers(m_window);
			}
			Shutdown();
		}
	private:
		void NewFrame()
		{
			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();
			ImGui::NewFrame();
		}
		void UpdateGraphicScene()
		{
			static_cast<Derived*>(this)->UpdateGraphicScene();
		}
		void OnRender()
		{
			static_cast<Derived*>(this)->OnRender();
		}
		void Render()
		{
			ImGui::Render();
			int display_w, display_h;
			glfwGetFramebufferSize(m_window, &display_w, &display_h);
			glViewport(0, 0, display_w, display_h);
			//render
			OnRender();

			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		}
	public:
		void Shutdown()
		{
			ImGui_ImplOpenGL3_Shutdown();
			ImGui_ImplGlfw_Shutdown();
			ImGui::DestroyContext();
			glfwDestroyWindow(m_window);
			glfwTerminate();
		}
	private:
		GLFWwindow* m_window;
	};
}




