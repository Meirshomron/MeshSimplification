#include "MovableGLM.h"
#include <iostream>

using namespace glm;

static void printMat(const glm::mat4 &mat)
	{
		printf(" matrix: \n");
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
				std::cout<<mat[j][i];
			std::cout<<std::endl;
			
		}
	}

vec3 MovableGLM::findAxis(vec3 vec) const
{
	return vec3(transpose( rotateMat)*vec4(vec,1));
}

MovableGLM::MovableGLM()
{
	translateMat[0] = mat4(1);  //translation to general point
	translateMat[1] = mat4(1);  //translation to COM
	rotateMat = mat4(1);     //rotation around general point or (0,0,0) of global coordinate
	scaleFactor = vec3(1);
}

mat4 MovableGLM::makeTransScale(const mat4 & prevTransformations) const
{
	return prevTransformations * makeTrans() * scale(mat4(1), scaleFactor);
}

void MovableGLM::copyTranslations(MovableGLM *mGLM)
{
	for (size_t i = 0; i < 2; i++)
	{
		translateMat[i] = mGLM->translateMat[i];
	}
	rotateMat = mGLM->rotateMat;
	//TODO: update rotation 
}


mat4 MovableGLM::makeTrans(const mat4 &prevTransformations) const
{
	return prevTransformations * makeTrans();
}

mat4 MovableGLM::makeTrans() const
{
	return  translateMat[0] * rotateMat * translateMat[1] ;
}


void MovableGLM::myRotate(float ang,const glm::vec3 &vec)
{
	

	rotateMat = rotate(rotateMat,ang,vec);

}

void MovableGLM::myTranslate(const vec3 &vec, int indx)
{
	translateMat[indx] = translate(translateMat[indx], scaleFactor * vec ) ;
	//printMat(translateMat[indx]);
}

void MovableGLM::myScale(const vec3 & vec)
{
	scaleFactor = scaleFactor*vec;
}

void MovableGLM::globalSystemRot(float ang,const vec3 &vec)
{
		rotateMat = rotate(mat4(1),ang,vec) * rotateMat;
}

void MovableGLM::translateInSystem(const MovableGLM  &system,const vec3 &vec, int indx, bool toScale)
{
	vec3 tmp;
	if (toScale)
		tmp = system.findAxis(scaleFactor * vec);
	else
		tmp = system.findAxis(vec);
	translateMat[indx] = translate(translateMat[indx], tmp);	
}

void MovableGLM::changeCenterOfRotation(const vec3 & Pvec)
{
	myTranslate(Pvec, 0 );
	myTranslate(-Pvec, 1);
}

void MovableGLM::clearTrans()
{
	translateMat[0] = mat4(1);
	translateMat[1] = mat4(1);
	rotateMat = mat4(1);
}

vec4 MovableGLM::getTraslate(const vec4 & vec)
{
	mat4 mat = makeTrans();
	return mat[3];
}

mat4 MovableGLM::getCenterOfRotation(const glm::mat4 &prevTransformations,bool addRotation)
{
	if(addRotation)
		return prevTransformations * translateMat[0] * rotateMat ;
	else
		return prevTransformations * translateMat[0];
}

glm::vec3 MovableGLM::getPointInSystem(const glm::mat4 &prevTransformations,const glm::vec3 &point)
{
	return vec3(makeTransScale(prevTransformations) * vec4(point,1));
}
	
glm::vec3 MovableGLM::getVectorInSystem(const glm::mat4 &prevTransformations,const glm::vec3 &vec)
{
	return vec3(makeTrans(prevTransformations) * vec4(vec,0));
}