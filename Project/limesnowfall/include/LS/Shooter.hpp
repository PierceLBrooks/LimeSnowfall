
// Author: Pierce Brooks

#ifndef LS_SHOOTER_HPP
#define LS_SHOOTER_HPP

#include <SFML3D/Graphics/Transformable.hpp>

namespace LS
{
    class Bullet;

    class Shooter : public sf3d::Transformable
    {
        public:
            Shooter();
            virtual ~Shooter();
            virtual bool hurt(Bullet* bullet) = 0;
    };
}

#endif // LS_SHOOTER_HPP
