
// Author: Pierce Brooks

#ifndef LS_SHOOTER_HPP
#define LS_SHOOTER_HPP

#include <SFML3D/Graphics/Transformable.hpp>
#include <LS/Ownable.hpp>

namespace LS
{
    class Bullet;
    class Game;

    class Shooter : public Ownable<Game*>, public sf3d::Transformable
    {
        public:
            Shooter(Game* owner);
            virtual ~Shooter();
            virtual bool hurt(Bullet* bullet) = 0;
            Game* getOwner() const;
        private:
            Game* owner;
    };
}

#endif // LS_SHOOTER_HPP
