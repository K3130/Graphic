#include "Graphic.h"


void Graphic::Init(int aWidth, int aHeight, const char* aTitle, ImVec4 aClearColor)
{
	m_clear_color = aClearColor;
	//-------------------------------------------
	// Setup window
	if (!glfwInit())
	{
		std::cerr << "Failed to initialize GLFW" << std::endl;
	}
	// GL 3.0 + GLSL 130
	const char* glsl_version = "#version 150";
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
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
		Update();
		Render();
		glfwSwapBuffers(m_window);
	}
	Shutdown();
}

void Graphic::NewFrame()
{
	// feed inputs to dear imgui, start new frame
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
}

void Graphic::Update()
{
	// render your GUI
	ImGui::Begin("Test");


	ImGui::End();
}

void Graphic::Render()
{
	// Render dear imgui into screen
	ImGui::Render();
	int display_w, display_h;
	glfwGetFramebufferSize(m_window, &display_w, &display_h);
	glViewport(0, 0, display_w, display_h);

	
	glClearColor(m_clear_color.x * m_clear_color.w, m_clear_color.y * m_clear_color.w, m_clear_color.z * m_clear_color.w, m_clear_color.w);
	glClear(GL_COLOR_BUFFER_BIT);
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

}

void Graphic::Shutdown()
{
	// Cleanup
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
	//--
	glfwDestroyWindow(m_window);
	glfwTerminate();
}


//#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
//int main()
//{
//	Graphic graphic;
//	graphic.Init(640, 480, "Test title", ImVec4(0.45f, 0.55f, 0.60f, 1.00f));
//
//	
//
//	return 0;
//}

