#version 120

attribute vec3 position;
attribute vec2 texCoord;
attribute vec3 normal;
attribute vec3 color;

uniform mat4 MVP;
uniform mat4 Normal;

//varying vec3 color0;

void main()
{
	//color0 = color;
	gl_Position = MVP * vec4(position, 1.0);
}
