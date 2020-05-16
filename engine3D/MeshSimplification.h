#pragma once

#include <iostream>
#include <algorithm>
#include <glm/glm.hpp>
#include <vector>
#include <list>
#include <string>
#include <map>

using namespace std;
using namespace glm;

/* 
* Change this value to the wanted simplification.
* NOTE: Pay attention to the object the main loads.
* MAX_FACES = the maximum number of faces the simplyfied OBJ will have.
*/
#define MAX_FACES 100

struct OBJIndex
{
	unsigned int vertexIndex;
	unsigned int uvIndex;
	unsigned int normalIndex;
	bool operator<(const OBJIndex& other) const { return vertexIndex < other.vertexIndex; }
	bool operator==(const OBJIndex& other) const { return vertexIndex == other.vertexIndex; }
};

struct Edge 
{
	OBJIndex firstVertex;
	OBJIndex secondVertex;
	float edgeError = 0;
	mat4 edgeQ;
	vec3 newPos;

	// Edge struct comperators

	bool operator==(const Edge& other) const
	{
		return (firstVertex.vertexIndex == other.firstVertex.vertexIndex && secondVertex.vertexIndex == other.secondVertex.vertexIndex) || (secondVertex.vertexIndex == other.firstVertex.vertexIndex && firstVertex.vertexIndex == other.secondVertex.vertexIndex);
	}
	bool operator()(const Edge& first, const Edge& second) const
	{
		return first < second;
	}
	bool operator < (const Edge& other)const 
	{
		if (firstVertex.vertexIndex < other.firstVertex.vertexIndex)
			return true;
		else 
		{
			if (firstVertex.vertexIndex == other.firstVertex.vertexIndex)
				return (secondVertex.vertexIndex < other.secondVertex.vertexIndex);
			else
				return false;
		}
	}
};

// Edges comperator.
struct compEdgeErr
{
	bool operator()(const struct Edge& e1, const struct Edge& e2) const
	{
		if (e2.edgeError < e1.edgeError)
			return true;
		return false;
	}
};

class MeshSimplification
{
public:
	MeshSimplification(list<OBJIndex> OBJIndices, vector<vec3> vertices);
	void start();
	vector<vec3> getVertices();
	list<OBJIndex> getIndices();
	~MeshSimplification();

private:
	vector<Edge> removeDups(vector<Edge> toRemove);
	void initEdgeVector();
	void initVertexNeighbor();
	void buildHeap();
	void calcFaces(int firstEdgeInd, int secondEdgeInd);
	vec4 getOptimalPos(mat4 m, vec4 Y);
	vec4 calcOptimalPos(Edge& e, mat4 m);
	void calcEdgeError(struct Edge &e);
	mat4 calcVertexError(int vertexIndex);
	bool isTriangle(int second, int third);
	void printEdgeVector(vector<Edge> vec);
	void printFaces();
	void printNeighbors();

	vector<Edge> m_edgeVector;
	multimap<int, int> m_vertexNeighbor;
	vector<mat4> m_errors;
	list<OBJIndex> m_OBJIndices;
	vector<vec3> m_vertices;
};