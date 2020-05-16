#define GLEW_STATIC
#include <GL\glew.h>
#include "scene.h"
#include <iostream>

using namespace std;




Scene::Scene()
{
	cameras.push_back(new Camera(glm::vec3(0,0,-15.0f),60.0f,1.0f,0.1f,100.0f));
	pickedShape = 0;
	glLineWidth(3);
}

Scene::Scene(glm::vec3 position,float angle,float hwRelation,float near, float far)
{
	glLineWidth(3);
	cameras.push_back(new Camera(position,angle,hwRelation,near,far));
	pickedShape = 0;
	LineVertex axisVertices[] = 
	{
		LineVertex(glm::vec3(1,0,0),glm::vec3(1,0,0)),
		LineVertex(glm::vec3(-1,0,0),glm::vec3(1,0,0)),
		LineVertex(glm::vec3(0,1,0),glm::vec3(0,1,0)),
		LineVertex(glm::vec3(0,-1,0),glm::vec3(0,1,0)),
		LineVertex(glm::vec3(0,0,1),glm::vec3(0,0,1)),
		LineVertex(glm::vec3(0,0,-1),glm::vec3(0,0,1)),
	};

	unsigned int axisIndices[] = 
	{
		0,1,
		2,3,
		4,5
	};
	axisMesh = new Shape(axisVertices,sizeof(axisVertices)/sizeof(axisVertices[0]),axisIndices, sizeof(axisIndices)/sizeof(axisIndices[0]));
}

	void Scene::addShape(int type)
	{
		shapes.push_back(new Shape(*shapes[type]));
	}

	// fileName contain the OBJ file to parse
	// simplifyFlag = 0 -> load OBJ as is
	// simplifyFlag = 1 -> load OBJ and simplyfy it 
	void Scene::addShape(const std::string& fileName, glm::vec3 position, int simplifyFlag)
	{
		Shape* newShape = new Shape(fileName, simplifyFlag);
		newShape->myTranslate(position, 1);
		newShape->changeCenterOfRotation(position);			
		shapes.push_back(newShape);
	}

	// fileName contain the OBJ file to parse
	// textureFileName contain the texture file to apply
	// simplifyFlag = 0 -> load OBJ as is
	// simplifyFlag = 1 -> load OBJ and simplyfy it 
	void Scene::addShape(const std::string& fileName,const std::string& textureFileName, int simplifyFlag)
	{
		shapes.push_back(new Shape(fileName,textureFileName, simplifyFlag));
	}

	void Scene::addShape(Vertex* vertices, unsigned int numVertices, unsigned int* indices, unsigned int numIndices)
	{
		shapes.push_back(new Shape(vertices,numVertices,indices,numIndices));
	}
	
	void Scene::addShape(Vertex* vertices, unsigned int numVertices, unsigned int* indices, unsigned int numIndices, const std::string &textureFlieName)
	{
		shapes.push_back(new Shape(vertices,numVertices,indices,numIndices,textureFlieName));
	}

	void Scene::addShader(const std::string& fileName)
	{
		shaders.push_back(new Shader(fileName));
	}

	glm::mat4 Scene::GetViewProjection(int indx) const
	{
		return cameras[indx]->GetViewProjection();
	}

	glm::mat4 Scene::GetShapeTransformation() const
	{
		return shapes[pickedShape]->makeTrans();
	}
	
	void Scene::draw(int shaderIndx,int cameraIndx,bool drawAxis)
	{
		glm::mat4 Normal = makeTrans();
		glm::mat4 MVP = cameras[0]->GetViewProjection() * Normal;
		
		for (int i = 0; i < shapes.size();i++)
		{

			shapes[i]->myRotate(0.01, glm::vec3(0, 1, 0));			//@Edited

			shaders[shaderIndx]->Bind();

			glm::mat4 MVP1 = MVP * shapes[i]->makeTransScale(glm::mat4(1));
			glm::mat4 Normal1 = Normal * shapes[i]->makeTrans();
			shaders[shaderIndx]->Update(MVP1,Normal1,i);
			shapes[i]->draw(GL_TRIANGLES);
		}

		if(shaderIndx==0 && drawAxis)
		{
			shaders[shaderIndx]->Bind();
			shaders[shaderIndx]->Update(cameras[0]->GetViewProjection()*glm::scale(glm::vec3(10,10,10)),Normal*glm::scale(glm::vec3(10,10,10)),0);
			axisMesh->draw(GL_LINES); //main axis
		}
	}

	void Scene::shapeTransformation(int type,float amt)
	{
		    switch (type)
			{
			case xLocalTranslate:
				
				break;
			case yLocalTranslate:
				
				break;
			case zLocalTranslate:
				
				break;
			case xGlobalTranslate:
				
				break;
			case yGlobalTranslate:
				
				break;
			case zGlobalTranslate:
				
				break;
			case xLocalRotate:
				
				break;
			case yLocalRotate:
				
				break;
			case zLocalRotate:
				
				break;
			case xGlobalRotate:
				break;
			case yGlobalRotate:
				break;
			case zGlobalRotate:
				break;
			case xScale:
				break;
			case yScale:
				break;
			case zScale:
			
				break;
			case xCameraTranslate: //camera plane translate
				
				break;
			case yCameraTranslate:
				
				break;
			case zCameraTranslate:
				
				break;
			default:
				break;
			}
	}
	
	void Scene::resize(int width,int height,int near,int far)
	{
		glViewport(0,0,width,height);
		cameras[0]->setProjection((float)width/(float)height,near,far);
	}

	Scene::~Scene(void)
{
	for (Shape* shp : shapes)
		{
			delete shp;
		}
	for (Camera* cam : cameras)
		{
			delete cam;
		}
	for(Shader* sdr: shaders)
		{
			delete sdr;
		}
	if (axisMesh)
	{
		delete axisMesh;
	}	
}
