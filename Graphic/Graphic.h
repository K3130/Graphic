#pragma once

#include "common.h"

class Graphic
{
public:
	Graphic() : m_window(nullptr), m_clear_color(ImVec4({})) {}
	void Init(int aWidth, int aHeight, const char* aTitle, ImVec4 aClearColor);
private:
	void NewFrame();
	virtual void Update();
	void Render();
	void Shutdown();
private:
	GLFWwindow* m_window;
	ImVec4 m_clear_color;
};



