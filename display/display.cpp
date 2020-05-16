#define GLEW_STATIC
#include <GL/glew.h>
#include <iostream>
#include "display.h"

bool Display::toClose()
{
	return glfwWindowShouldClose(m_window);
}

void Display::pullEvent()
{
	glfwPollEvents();
}

Display::Display(int width, int height, const std::string& title)
{
	/* Initialize the library */
    if (!glfwInit())
        error =  -1;

	m_window = glfwCreateWindow(640, 480, title.c_str(), NULL, NULL);
	if(!m_window)
	{
		glfwTerminate();
		error = -1;
	}
	glfwMakeContextCurrent(m_window);
	
	GLenum res = glewInit();
    if(res != GLEW_OK)
   {
		std::cerr << "Glew failed to initialize!" << std::endl;
    }

	glEnable(GL_DEPTH_TEST);
}

Display::~Display()
{
	glfwDestroyWindow(m_window);
	glfwTerminate();
}

void Display::Clear(float r, float g, float b, float a)
{
	glClearColor(r, g, b, a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Display::SwapBuffers()
{
	glfwSwapBuffers(m_window);
}
