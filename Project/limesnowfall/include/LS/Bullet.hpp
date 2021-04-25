
// Author: Pierce Brooks

#ifndef LS_BULLET_HPP
#define LS_BULLET_HPP

#include <LS/Shooter.hpp>
#include <LS/Ownable.hpp>
#include <SFML3D/Graphics/RenderTexture.hpp>
#include <SFML3D/Graphics/RectangleShape.hpp>

namespace LS
{
    class Bullet : public Ownable<Shooter*>, public sf3d::Transformable
    {
        public:
            Bullet(Shooter* owner, float angle);
            virtual ~Bullet();
            Shooter* getOwner() const;
            bool update(sf3d::RenderTexture* window, float deltaTime);
        private:
            sf3d::RectangleShape* shape;
            Shooter* owner;
            float angle;
            float pi;
            float life;
    };
}

#endif // LS_BULLET_HPP
