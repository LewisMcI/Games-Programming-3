#include "ObjectLoader.h"
#include <fstream>
#include <iostream>
#include <algorithm>
#include <map>

static bool CompareOBJIndexPtr(const OBJIndex* a, const OBJIndex* b);
static inline unsigned int FindNextChar(unsigned int start, const char* str, unsigned int length, char token);
static inline unsigned int ParseOBJIndexValue(const std::string& token, unsigned int start, unsigned int end);
static inline double ParseOBJFloatValue(const std::string& token, unsigned int start, unsigned int end);
static inline std::vector<std::string> SplitString(const std::string& s, char delim);

OBJModel::OBJModel(const std::string& fileName)
{
    hasUVs = false;
    hasNormals = false; 
    FILE* newFile = fopen(fileName.c_str(), "r");

    char line[1024];
    while (fgets(line, sizeof(line), newFile)) {

            switch (line[0])
            {
                case 'v':
                    if (line[1] == 't')
                        this->uvs.push_back(parseOBJVec2(line));
                    else if (line[1] == 'n')
                        this->normals.push_back(parseOBJVec3(line));
                    else if (line[1] == ' ' || line[1] == '\t')
                        this->vertices.push_back(parseOBJVec3(line));
                    break;
                case 'f':
                    createOBJFace(line);
                    break;
                default: 
                    break;
            };
    }
}

void IndexedModel::calcNormals()
{
    for (unsigned int i = 0; i < indices.size(); i += 3)
    {
        int i0 = indices[i];
        int i1 = indices[i + 1];
        int i2 = indices[i + 2];

        glm::vec3 v1 = positions[i1] - positions[i0];
        glm::vec3 v2 = positions[i2] - positions[i0];

        glm::vec3 normal = glm::normalize(glm::cross(v1, v2));

        normals[i0] += normal;
        normals[i1] += normal;
        normals[i2] += normal;
    }

    for (unsigned int i = 0; i < positions.size(); i++)
        normals[i] = glm::normalize(normals[i]);
}

IndexedModel OBJModel::toIndexedModel()
{
    IndexedModel result;
    IndexedModel normalModel;

    unsigned int numIndices = OBJIndices.size();

    std::vector<OBJIndex*> indexLookup;

    for (unsigned int i = 0; i < numIndices; i++)
        indexLookup.push_back(&OBJIndices[i]);

    std::sort(indexLookup.begin(), indexLookup.end(), CompareOBJIndexPtr);

    std::map<OBJIndex, unsigned int> normalModelIndexMap;
    std::map<unsigned int, unsigned int> indexMap;

    for (unsigned int i = 0; i < numIndices; i++)
    {
        OBJIndex* currentIndex = &OBJIndices[i];

        glm::vec3 currentPosition = vertices[currentIndex->vertexIndex];
        glm::vec2 currentTexCoord;
        glm::vec3 currentNormal;

        if (hasUVs)
            currentTexCoord = uvs[currentIndex->uvIndex];
        else
            currentTexCoord = glm::vec2(0, 0);

        if (hasNormals)
            currentNormal = normals[currentIndex->normalIndex];
        else
            currentNormal = glm::vec3(0, 0, 0);

        unsigned int normalModelIndex;
        unsigned int resultModelIndex;

        //Create model to properly generate normals on
        std::map<OBJIndex, unsigned int>::iterator it = normalModelIndexMap.find(*currentIndex);
        if (it == normalModelIndexMap.end())
        {
            normalModelIndex = normalModel.positions.size();

            normalModelIndexMap.insert(std::pair<OBJIndex, unsigned int>(*currentIndex, normalModelIndex));
            normalModel.positions.push_back(currentPosition);
            normalModel.texCoords.push_back(currentTexCoord);
            normalModel.normals.push_back(currentNormal);
        }
        else
            normalModelIndex = it->second;

        //Create model which properly separates texture coordinates
        unsigned int previousVertexLocation = findLastVertexIndex(indexLookup, currentIndex, result);

        if (previousVertexLocation == (unsigned int)-1)
        {
            resultModelIndex = result.positions.size();

            result.positions.push_back(currentPosition);
            result.texCoords.push_back(currentTexCoord);
            result.normals.push_back(currentNormal);
        }
        else
            resultModelIndex = previousVertexLocation;

        normalModel.indices.push_back(normalModelIndex);
        result.indices.push_back(resultModelIndex);
        indexMap.insert(std::pair<unsigned int, unsigned int>(resultModelIndex, normalModelIndex));
    }

    if (!hasNormals)
    {
        normalModel.calcNormals();

        for (unsigned int i = 0; i < result.positions.size(); i++)
            result.normals[i] = normalModel.normals[indexMap[i]];
    }

    return result;
};

unsigned int OBJModel::findLastVertexIndex(const std::vector<OBJIndex*>& indexLookup, const OBJIndex* currentIndex, const IndexedModel& result)
{
    unsigned int start = 0;
    unsigned int end = indexLookup.size();
    unsigned int current = (end - start) / 2 + start;
    unsigned int previous = start;

    while (current != previous)
    {
        OBJIndex* testIndex = indexLookup[current];

        if (testIndex->vertexIndex == currentIndex->vertexIndex)
        {
            unsigned int countStart = current;

            for (unsigned int i = 0; i < current; i++)
            {
                OBJIndex* possibleIndex = indexLookup[current - i];

                if (possibleIndex == currentIndex)
                    continue;

                if (possibleIndex->vertexIndex != currentIndex->vertexIndex)
                    break;

                countStart--;
            }

            for (unsigned int i = countStart; i < indexLookup.size() - countStart; i++)
            {
                OBJIndex* possibleIndex = indexLookup[current + i];

                if (possibleIndex == currentIndex)
                    continue;

                if (possibleIndex->vertexIndex != currentIndex->vertexIndex)
                    break;
                else if ((!hasUVs || possibleIndex->uvIndex == currentIndex->uvIndex)
                    && (!hasNormals || possibleIndex->normalIndex == currentIndex->normalIndex))
                {
                    glm::vec3 currentPosition = vertices[currentIndex->vertexIndex];
                    glm::vec2 currentTexCoord;
                    glm::vec3 currentNormal;

                    if (hasUVs)
                        currentTexCoord = uvs[currentIndex->uvIndex];
                    else
                        currentTexCoord = glm::vec2(0, 0);

                    if (hasNormals)
                        currentNormal = normals[currentIndex->normalIndex];
                    else
                        currentNormal = glm::vec3(0, 0, 0);

                    for (unsigned int j = 0; j < result.positions.size(); j++)
                    {
                        if (currentPosition == result.positions[j]
                            && ((!hasUVs || currentTexCoord == result.texCoords[j])
                                && (!hasNormals || currentNormal == result.normals[j])))
                        {
                            return j;
                        }
                    }
                }
            }

            return -1;
        }
        else
        {
            if (testIndex->vertexIndex < currentIndex->vertexIndex)
                start = current;
            else
                end = current;
        }

        previous = current;
        current = (end - start) / 2 + start;
    }

    return -1;
}
#include <sstream>

static inline std::vector<std::string> NewSplitString(const std::string& s, char delim)
{
    std::vector<std::string> elems;
    std::size_t start = 0;
    std::size_t end = s.find(delim);

    while (end != std::string::npos)
    {
        elems.emplace_back(s.c_str() + start, end - start);
        start = end + 1;
        end = s.find(delim, start);
    }

    elems.emplace_back(s.c_str() + start);
    return elems;
}

void OBJModel::createOBJFace(const std::string& line)
{
    std::vector<std::string> tokens = NewSplitString(line, ' ');
    this->OBJIndices.push_back(parseOBJIndex(tokens[1], &this->hasUVs, &this->hasNormals));
    this->OBJIndices.push_back(parseOBJIndex(tokens[2], &this->hasUVs, &this->hasNormals));
    this->OBJIndices.push_back(parseOBJIndex(tokens[3], &this->hasUVs, &this->hasNormals));

    if (tokens.size() > 4)
    {
        this->OBJIndices.push_back(parseOBJIndex(tokens[1], &this->hasUVs, &this->hasNormals));
        this->OBJIndices.push_back(parseOBJIndex(tokens[3], &this->hasUVs, &this->hasNormals));
        this->OBJIndices.push_back(parseOBJIndex(tokens[4], &this->hasUVs, &this->hasNormals));
    }
}




// Function to parse an OBJ index from a given token
// Also updates whether UVs and normals are present
OBJIndex OBJModel::parseOBJIndex(const std::string& token, bool* hasUVs, bool* hasNormals)
{
    // Get the length of the token and convert it to a character array
    unsigned int tokenLength = token.length();
    const char* tokenString = token.c_str();

    // Define the start and end of the vertex index
    unsigned int vertIndexStart = 0;
    unsigned int vertIndexEnd = FindNextChar(vertIndexStart, tokenString, tokenLength, '/');

    // Initialize the result structure to store vertex, UV, and normal indices
    OBJIndex result;
    result.vertexIndex = ParseOBJIndexValue(token, vertIndexStart, vertIndexEnd);
    result.uvIndex = 0;       // Initialize UV index to 0
    result.normalIndex = 0;   // Initialize normal index to 0

    // If there are no more characters in the token, return the result
    if (vertIndexEnd >= tokenLength)
        return result;
    // Move to the next part (UV) and extract the UV index
    vertIndexStart = vertIndexEnd + 1;
    vertIndexEnd = FindNextChar(vertIndexStart, tokenString, tokenLength, '/');

    result.uvIndex = ParseOBJIndexValue(token, vertIndexStart, vertIndexEnd);
    *hasUVs = true;  // Indicate that UVs are present by updating the boolean pointer

    // If there are no more characters in the token, return the result
    if (vertIndexEnd >= tokenLength)
        return result;

    // Move to the next part (normal) and extract the normal index
    vertIndexStart = vertIndexEnd + 1;
    vertIndexEnd = FindNextChar(vertIndexStart, tokenString, tokenLength, '/');

    result.normalIndex = ParseOBJIndexValue(token, vertIndexStart, vertIndexEnd);
    *hasNormals = true;  // Indicate that normals are present by updating the boolean pointer

    // Return the final result containing vertex, UV, and normal indices
    return result;
}


glm::vec3 OBJModel::parseOBJVec3(const std::string& line)
{
    unsigned int tokenLength = line.length();
    const char* tokenString = line.c_str();

    unsigned int vertIndexStart = 2;

    while (vertIndexStart < tokenLength)
    {
        if (tokenString[vertIndexStart] != ' ')
            break;
        vertIndexStart++;
    }

    unsigned int vertIndexEnd = FindNextChar(vertIndexStart, tokenString, tokenLength, ' ');

    double x = ParseOBJFloatValue(line, vertIndexStart, vertIndexEnd);

    vertIndexStart = vertIndexEnd + 1;
    vertIndexEnd = FindNextChar(vertIndexStart, tokenString, tokenLength, ' ');

    double y = ParseOBJFloatValue(line, vertIndexStart, vertIndexEnd);

    vertIndexStart = vertIndexEnd + 1;
    vertIndexEnd = FindNextChar(vertIndexStart, tokenString, tokenLength, ' ');

    double z = ParseOBJFloatValue(line, vertIndexStart, vertIndexEnd);

    return glm::vec3(x, y, z);

    //glm::vec3(atof(tokens[1].c_str()), atof(tokens[2].c_str()), atof(tokens[3].c_str()))
}

glm::vec2 OBJModel::parseOBJVec2(const std::string& line)
{
    unsigned int tokenLength = line.length();
    const char* tokenString = line.c_str();

    unsigned int vertIndexStart = 3;

    while (vertIndexStart < tokenLength)
    {
        if (tokenString[vertIndexStart] != ' ')
            break;
        vertIndexStart++;
    }

    unsigned int vertIndexEnd = FindNextChar(vertIndexStart, tokenString, tokenLength, ' ');

    double x = ParseOBJFloatValue(line, vertIndexStart, vertIndexEnd);

    vertIndexStart = vertIndexEnd + 1;
    vertIndexEnd = FindNextChar(vertIndexStart, tokenString, tokenLength, ' ');

    double y = ParseOBJFloatValue(line, vertIndexStart, vertIndexEnd);

    return glm::vec2(x, y);
}

static bool CompareOBJIndexPtr(const OBJIndex* a, const OBJIndex* b)
{
    return a->vertexIndex < b->vertexIndex;
}

static inline unsigned int FindNextChar(unsigned int start, const char* str, unsigned int length, char token)
{
    unsigned int result = start;
    while (result < length)
    {
        result++;
        if (str[result] == token)
            break;
    }

    return result;
}

static inline unsigned int ParseOBJIndexValue(const std::string& token, unsigned int start, unsigned int end)
{
    return atoi(token.substr(start, end - start).c_str()) - 1;
}

static inline double ParseOBJFloatValue(const std::string& token, unsigned int start, unsigned int end)
{
    return atof(token.substr(start, end - start).c_str());
}

static inline std::vector<std::string> SplitString(const std::string& s, char delim)
{
    std::vector<std::string> elems;

    const char* cstr = s.c_str();
    unsigned int strLength = s.length();
    unsigned int start = 0;
    unsigned int end = 0;

    while (end <= strLength)
    {
        while (end <= strLength)
        {
            if (cstr[end] == delim)
                break;
            end++;
        }

        elems.push_back(s.substr(start, end - start));
        start = end + 1;
        end = start;
    }

    return elems;
}