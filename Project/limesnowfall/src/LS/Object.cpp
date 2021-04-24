
// Author: Pierce Brooks

#include <LS/Object.hpp>

LS::Object::FaceData::FaceData()
{
    
}

LS::Object::FaceData::~FaceData()
{
    
}

LS::Object::Object()
{
    
}

LS::Object::~Object()
{
    
}

bool LS::Object::loadFromFile(const std::string& filename)
{
    // Open our model file
    std::ifstream modelFile(filename.c_str());
    if (!modelFile.is_open())
    {
        return false;
    }

    // Parse the model file line by line
    std::string line;
    std::istringstream lineStream;
    std::string token;

    while (true)
    {
        std::getline(modelFile, line);

        // Break on error or failure to read (end of file)
        if ((modelFile.bad()) || (modelFile.fail()))
        {
            break;
        }

        lineStream.clear();
        lineStream.str(line);
        lineStream >> token;

        if (token == "v")
        {
            // Handle vertex positions
            sf3d::Vector3f position;
            lineStream >> position.x >> position.y >> position.z;
            vertexPositions.push_back(position);
        }
        else if (token == "vt")
        {
            // Handle vertex texture coordinates
            sf3d::Vector2f coordinate;
            lineStream >> coordinate.x >> coordinate.y;
            vertexTextureCoordinates.push_back(coordinate);
        }
        else if (token == "vn")
        {
            // Handle vertex normals
            sf3d::Vector3f normal;
            lineStream >> normal.x >> normal.y >> normal.z;
            vertexNormals.push_back(normal);
        }
        else if (token == "f")
        {
            // Handle faces
            std::string vertexString0, vertexString1, vertexString2;

            lineStream >> vertexString0 >> vertexString1 >> vertexString2;

            sf3d::Vertex vertex0(makeVertex(vertexString0));
            sf3d::Vertex vertex1(makeVertex(vertexString1));
            sf3d::Vertex vertex2(makeVertex(vertexString2));

            addVertex(vertex0);
            addVertex(vertex1);
            addVertex(vertex2);

            unsigned int index = getVertexCount();

            addFace(index - 3, index - 2, index - 1);
        }
    }

    // Update the underlying polyhedron geometry
    update();

    return true;
}

sf3d::Vertex LS::Object::makeVertex(const std::string& indices)
{
    sf3d::Vertex vertex;
    std::istringstream indiceStream(indices);

    unsigned int positionIndex = 0;
    unsigned int textureCoordinateIndex = 0;
    unsigned int normalIndex = 0;
    char separator = 0;

    if (!(indiceStream >> positionIndex >> separator).good())
    {
        return vertex;
    }

    if (!(indiceStream >> textureCoordinateIndex >> separator).good())
    {
        return vertex;
    }

    if (!(indiceStream >> normalIndex).eof())
    {
        return vertex;
    }

    // .obj indices start at 1
    positionIndex -= 1;
    textureCoordinateIndex -= 1;
    normalIndex -= 1;

    if ((positionIndex >= vertexPositions.size()) ||
        (textureCoordinateIndex >= vertexTextureCoordinates.size()) ||
        (normalIndex >= vertexNormals.size()))
    {
        return vertex;
    }

    vertex.position = vertexPositions[positionIndex];
    vertex.texCoords = vertexTextureCoordinates[textureCoordinateIndex];
    vertex.normal = vertexNormals[normalIndex];

    // Not needed, but just for demonstration
    vertex.color = getColor();

    return vertex;
}

