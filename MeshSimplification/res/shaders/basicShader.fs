#version 130

in vec2 texCoord0;
varying vec3 normal0;
varying vec3 color0;

uniform sampler2D sampler;
uniform vec3 lightDirection;
uniform vec3 lightColor;

void main()
{
    vec3 tmp =  color0 ;
   
	gl_FragColor =  clamp(vec4(tmp,1.0), 0.0, 1.0);
}
