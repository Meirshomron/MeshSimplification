#version 130 

//varying vec2 MCposition;
varying vec3 LightIntensity;
in vec2 TexCoord;
uniform sampler2D ourTexture;



void main()
{
	vec4 t = texture2D(ourTexture, TexCoord.xy);
	//vec4 t = texture2D(ourTexture, gl_TexCoord[0].xy);
	gl_FragColor = t * min(vec4(LightIntensity,1),1.0);
}