#include <iostream>
#include "display.h"
#include "inputManager.h"

Display display(DISPLAY_WIDTH, DISPLAY_HEIGHT, "OpenGL");	
Scene scn(glm::vec3(0.0f, 0.0f, -15.0f), CAM_ANGLE, relation, NEAR, FAR);

int main(int argc, char** argv)
{
	initCallbacks(display);
	
	// testboxNoUV - Start faces = 12
	//scn.addShape("./res/objs/testboxNoUV.obj", glm::vec3(-5, 0, 0), 0);
	//scn.addShape("./res/objs/testboxNoUV.obj", glm::vec3(5, 0, 0), 1);

	// monkey3 - Start faces = 4k (down to 2k)
	//scn.addShape("./res/objs/monkey3.obj", glm::vec3(-5, 0, 0), 0);
	//scn.addShape("./res/objs/monkey3.obj", glm::vec3(5, 0, 0), 1);

	// Wooden Crate - Start faces = 298 (down to 75)
	scn.addShape("./res/objs/Wooden Crate.obj", glm::vec3(-5, 0, 0), 0);
	scn.addShape("./res/objs/Wooden Crate.obj", glm::vec3(5, 0, 0), 1);
	
	scn.addShader("./res/shaders/basicShader");
	scn.addShader("./res/shaders/pickingShader");
		
	while(!display.toClose())
	{
		display.Clear(0.7f, 0.7f, 0.7f, 1.0f);
		scn.draw(0, 0, true);
		display.SwapBuffers();
		display.pullEvent();
	}

	return 0;
}
