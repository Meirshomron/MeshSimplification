#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class MovableGLM 
{
private:
	glm::mat4 translateMat[2];
	glm::mat4 rotateMat;
	glm::vec3 scaleFactor;
	glm::vec3 findAxis(glm::vec3 vec) const;

public:
	MovableGLM();
	virtual ~MovableGLM(){}
	glm::mat4 makeTransScale(const glm::mat4 &prevTransformations) const;
	glm::mat4 makeTransScale() const;
	glm::mat4 makeTrans(const glm::mat4 &prevTransformations) const;
	glm::mat4 makeTrans() const;

	void myRotate(float ang, const glm::vec3 &vec);
	void myTranslate(const glm::vec3 &vec, int indx);
	void myScale(const glm::vec3 &vec);
	void globalSystemRot(float ang, const glm::vec3 &vec);
	void changeCenterOfRotation(const glm::vec3 &Pvec);
	void clearTrans();
	void copyTranslations(MovableGLM *mGLM);
	void translateInSystem(const MovableGLM  &system,const glm::vec3 &vec, int indx, bool toScale);

	glm::vec4 getTraslate(const glm::vec4 &vec);
	glm::vec3 getPointInSystem(const glm::mat4 &prevTransformations,const glm::vec3 &point);
	glm::vec3 getVectorInSystem(const glm::mat4 &prevTransformations,const glm::vec3 &vec);
	glm::mat4 getCenterOfRotation(const glm::mat4 &prevTransformations,bool addRotation);
	
	static void printMat(const glm::mat4 &mat);

};