
// Author: Pierce Brooks

#ifndef LS_OBJECT_HPP
#define LS_OBJECT_HPP

#include <SFML3D/Graphics/Model.hpp>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

namespace LS
{
    class Object : public sf3d::Model
    {
        public:
            class FaceData
            {
                public:
                    FaceData();
                    virtual ~FaceData();
                    unsigned int position0;
                    unsigned int position1;
                    unsigned int position2;
                    unsigned int textureCoordinate0;
                    unsigned int textureCoordinate1;
                    unsigned int textureCoordinate2;
                    unsigned int normal0;
                    unsigned int normal1;
                    unsigned int normal2;
            };
            Object();
            virtual ~Object();
            bool loadFromFile(const std::string& filename);
        private:
            sf3d::Vertex makeVertex(const std::string& indices);
            std::vector<sf3d::Vector3f> vertexPositions;
            std::vector<sf3d::Vector2f> vertexTextureCoordinates;
            std::vector<sf3d::Vector3f> vertexNormals;
            std::vector<FaceData> faceData;
    };
}

#endif // LS_OBJECT_HPP
