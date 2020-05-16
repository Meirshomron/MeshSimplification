#ifndef LINEMESH_INCLUDED_H
#define LINEMESH_INCLUDED_H

#include <glm/glm.hpp>
#include <string>
#include <vector>
#include "obj_loader.h"

struct LineVertex
{
public:
	LineVertex(const glm::vec3& pos, const glm::vec3& color)
	{
		this->pos = pos;
		this->color = color;
	}

	glm::vec3* GetPos() { return &pos; }
	glm::vec3* GetColor() { return &color; }

private:
	glm::vec3 pos;
	glm::vec3 color;
	
};



class LineMesh
{
public:
	LineMesh(LineVertex* vertices, unsigned int numVertices, unsigned int* indices, unsigned int numIndices);

	void Draw();

	virtual ~LineMesh();
protected:
private:
	enum MeshBufferPositions
	{
	POSITION_VB,
	INDEX_VB,
	COLOR_VB
	};
	static const unsigned int NUM_BUFFERS = 3;
	void operator=(const LineMesh& mesh) {}
	LineMesh(const LineMesh& mesh) {}

    void InitLineMesh(const IndexedModel& model);

	unsigned int m_vertexArrayObject;
	unsigned int m_vertexArrayBuffers[NUM_BUFFERS];
	unsigned int m_numIndices;
};

#endif
