#include "shape.h"


Shape::Shape(const Shape& shape)
{
	if(shape.mesh)
		mesh = shape.mesh;
	if(shape.lineMesh)
		lineMesh = shape.lineMesh;
	tex = shape.tex;
	isCopy = true;
}

//@Edited
Shape::Shape(const std::string& fileName, int simplifyFlag){
	mesh = new Mesh(fileName, simplifyFlag);
	tex = 0;
	isCopy = false;
}
//@Edited
Shape::Shape(const std::string& fileName,const std::string& textureFileName, int simplifyFlag){
	mesh = new Mesh(fileName, simplifyFlag);
	tex = new Texture(textureFileName);
	isCopy = false;
}

Shape::Shape(Vertex* vertices, unsigned int numVertices, unsigned int* indices, unsigned int numIndices)
{
	mesh = new Mesh(vertices,numVertices,indices,numIndices);
	tex = 0; 
	isCopy = false;
}

Shape::Shape(LineVertex* vertices, unsigned int numVertices, unsigned int* indices, unsigned int numIndices)
{

	lineMesh = new LineMesh(vertices,numVertices,indices,numIndices);
	tex = 0; 
	isCopy = false;
}


Shape::Shape(Vertex* vertices, unsigned int numVertices, unsigned int* indices, unsigned int numIndices,const std::string& textureFileName)
{
	mesh = new Mesh(vertices,numVertices,indices,numIndices);
	tex = new Texture(textureFileName);
	isCopy = false;
}

void Shape::addMesh(Vertex* vertices, unsigned int numVertices,unsigned int* indices, unsigned int numIndices, const std::string& textureFileName)
{
	mesh = new Mesh(vertices,numVertices,indices,numIndices);
	tex = new Texture(textureFileName);
}

void Shape::addMesh(Vertex* vertices, unsigned int numVertices,unsigned int* indices, unsigned int numIndices)
{
	mesh = new Mesh(vertices,numVertices,indices,numIndices);
}

void Shape::addLineMesh(LineVertex* vertices, unsigned int numVertices,unsigned int* indices, unsigned int numIndices)
{
	lineMesh = new LineMesh(vertices,numVertices,indices,numIndices);
}

void Shape::draw(int mode)
{
	//transformations
	if(tex)
		tex->Bind();
	if(mesh)
		mesh->Draw(mode);
	if(lineMesh)
		lineMesh->Draw();
}

Shape::~Shape(void)
{
	if(!isCopy)
	{
		if(mesh)
 			delete mesh;
		if(lineMesh)
			delete lineMesh;
		if(tex)
			delete tex;
	}
}

void Shape::getPoints(std::list<glm::vec3> &pList)
{

}