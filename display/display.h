#ifndef DISPLAY_INCLUDED_H
#define DISPLAY_INCLUDED_H

#include <GLFW\glfw3.h>

#include <string>

class Display
{
public:

	Display(int width, int height, const std::string& title);

	void Clear(float r, float g, float b, float a);
	void SwapBuffers();
	bool toClose();
	void pullEvent();

	virtual ~Display();
	
	void operator=(const Display& display) {}
	Display(const Display& display) {}

	GLFWwindow* m_window;
	int error;
	
};

#endif
