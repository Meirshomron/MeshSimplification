#version 130 

varying vec3 LightIntensity;
//varying vec2 texCoord;
uniform sampler2D ourTexture;



void main()
{
	vec4 t = texture2D(ourTexture, gl_TexCoord[0].st);
	gl_FragColor =  t * min(vec4(LightIntensity,1),1.0);
	//gl_FragColor = LightIntensity;
}