#ifndef OBJ_LOADER_H
#define OBJ_LOADER_H

#include <glm/glm.hpp>
#include <vector>
#include <string>

struct OBJIndex
{
    unsigned int vertexIndex;
    unsigned int uvIndex;
    unsigned int normalIndex;

    bool operator<(const OBJIndex& r) const { return vertexIndex < r.vertexIndex; }
};

class IndexedModel
{
public:
    std::vector<glm::vec3> positions;
    std::vector<glm::vec2> texCoords;
    std::vector<glm::vec3> normals;
    std::vector<unsigned int> indices;

    void calcNormals();
};

class OBJModel
{
public:


    OBJModel(const std::string& fileName);

    IndexedModel toIndexedModel();
private:
    std::vector<OBJIndex> OBJIndices;
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec2> uvs;
    std::vector<glm::vec3> normals;

    bool hasUVs;
    bool hasNormals;
    unsigned int findLastVertexIndex(const std::vector<OBJIndex*>& indexLookup, const OBJIndex* currentIndex, const IndexedModel& result);
    void createOBJFace(const std::string& line);

    glm::vec2 parseOBJVec2(const std::string& line);
    glm::vec3 parseOBJVec3(const std::string& line);
    OBJIndex parseOBJIndex(const std::string& token, bool* hasUVs, bool* hasNormals);
};

#endif