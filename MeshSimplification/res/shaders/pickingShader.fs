#version 120

//varying vec3 color0;

uniform sampler2D sampler;
uniform vec3 lightDirection;
uniform vec3 lightColor;

void main()
{
	gl_FragColor = vec4(lightColor,1);
}
