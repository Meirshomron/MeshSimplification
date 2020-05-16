#pragma once   //maybe should be static class
#include "Scene.h"
#define M_PI 3.14159265359

const int DISPLAY_WIDTH = 800;
const int DISPLAY_HEIGHT = 600;
const float FAR = 1000.0f;
const float NEAR = 1.0f;
const float CAM_ANGLE = 45.0f;
float relation = (float)DISPLAY_WIDTH / (float)DISPLAY_HEIGHT;

extern Scene scn;

float factor = 1.0;

double x1 = 0, x2 = 0;
double ys1 = 0, y2 = 0;
float depth;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (action == GLFW_PRESS || action == GLFW_REPEAT)
	{
		switch (key)
		{
		case GLFW_KEY_ESCAPE:
		case GLFW_KEY_Q:

			glfwSetWindowShouldClose(window, GLFW_TRUE);
			break;
		case GLFW_KEY_RIGHT:
			scn.cameras[0]->MoveRight(-1.0f);
			break;
		case GLFW_KEY_LEFT:
			scn.cameras[0]->MoveRight(1.0f);

			break;
		case GLFW_KEY_UP:
			scn.cameras[0]->MoveForward(1.0f);

			break;
		case GLFW_KEY_DOWN:
			scn.cameras[0]->MoveForward(-1.0f);

			break;
		case GLFW_KEY_D:
			scn.cameras[0]->RotateY(-0.5);
			break;
		case GLFW_KEY_A:
			scn.cameras[0]->RotateY(0.5);
			break;
		case GLFW_KEY_S:
			scn.cameras[0]->Pitch(0.5);
			break;
		case GLFW_KEY_W:
			scn.cameras[0]->Pitch(-0.5);
			break;

		default:
			break;
		}
	}
}

void updatePosition(double xpos, double ypos)
{
	x1 = x2;
	x2 = xpos;
	ys1 = y2;
	y2 = ypos;
}

void window_size_callback(GLFWwindow* window, int width, int height)
{

	scn.resize(width, height, NEAR, FAR);
	relation = (float)width / (float)height;
}

void initCallbacks(const Display &display)
{
	glfwSetKeyCallback(display.m_window, key_callback);
	glfwSetWindowSizeCallback(display.m_window, window_size_callback);
	//glfwSetMouseButtonCallback(display.m_window,mouse_callback);
	//glfwSetScrollCallback(display.m_window, scroll_callback);
	//glfwSetCursorPosCallback(display.m_window , cursor_position_callback);
	//glfwSetInputMode(display.m_window,GLFW_STICKY_MOUSE_BUTTONS,1);
}