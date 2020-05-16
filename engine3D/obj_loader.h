#ifndef OBJ_LOADER_H_INCLUDED
#define OBJ_LOADER_H_INCLUDED

#include "MeshSimplification.h"

#include <glm/glm.hpp>
#include <vector>
#include <list>
#include <string>
#include <map>



struct IndexedModel
{
    std::vector<glm::vec3> positions;
    std::vector<glm::vec2> texCoords;
    std::vector<glm::vec3> normals;
	std::vector<glm::vec3> colors;
    std::vector<unsigned int> indices;
};

class OBJModel{
public:
    std::list<OBJIndex> OBJIndices;
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec2> uvs;
    std::vector<glm::vec3> normals;
	std::vector<glm::vec3> colors;
	
	bool hasUVs;
	
    bool hasNormals;
    
	OBJModel(const std::string& fileName, int simplifyFlag);											//Edited
	
    IndexedModel ToIndexedModel();


private:
    unsigned int FindLastVertexIndex(const std::vector<OBJIndex*>& indexLookup, const OBJIndex* currentIndex, const IndexedModel& result);
    void CreateOBJFace(const std::string& line);
    glm::vec2 ParseOBJVec2(const std::string& line);
    glm::vec3 ParseOBJVec3(const std::string& line);
    OBJIndex ParseOBJIndex(const std::string& token, bool* hasUVs, bool* hasNormals);
	void CalcNormals();

};

#endif // OBJ_LOADER_H_INCLUDED
