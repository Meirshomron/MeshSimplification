#ifndef SHADER_INCLUDED_H
#define SHADER_INCLUDED_H

#include <string>
#include "glm\glm.hpp"

class Shader
{
public:
	Shader(const std::string& fileName);

	void Bind();
	void Update( glm::mat4 MVP ,glm::mat4 Normal , int const shpIndx);

	virtual ~Shader();
protected:
private:
	static const unsigned int NUM_SHADERS = 2;
	static const unsigned int NUM_UNIFORMS = 4;
	void operator=(const Shader& shader) {}
	Shader(const Shader& shader) {}
	
	std::string LoadShader(const std::string& fileName);
	void CheckShaderError(unsigned int shader, unsigned int flag, bool isProgram, const std::string& errorMessage);
	unsigned int CreateShader(const std::string& text, unsigned int type);

	unsigned int m_program;
	unsigned int m_shaders[NUM_SHADERS];
	unsigned int m_uniforms[NUM_UNIFORMS];
};

#endif
