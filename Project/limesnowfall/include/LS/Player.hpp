
// Author: Pierce Brooks

#ifndef LS_PLAYER_HPP
#define LS_PLAYER_HPP

#include <LS/Ownable.hpp>
#include <SFML3D/System/Vector2.hpp>
#include <SFML3D/Graphics/Texture.hpp>
#include <SFML3D/Graphics/Sprite.hpp>

namespace LS
{
    class Game;

    class Player : public Ownable<Game*>
    {
        public:
            Player(Game* owner, const sf3d::Vector2u& position);
            virtual ~Player();
            bool shoot();
            void move(const sf3d::Vector2i& movement);
            Game* getOwner() const;
            sf3d::Sprite* getSprite() const;
            const sf3d::Vector2u& getPosition() const;
            void setPosition(const sf3d::Vector2u& position);
        private:
            Game* owner;
            sf3d::Texture* texture;
            sf3d::Sprite* sprite;
            sf3d::Vector2u position;
    };
}

#endif // LS_PLAYER_HPP
