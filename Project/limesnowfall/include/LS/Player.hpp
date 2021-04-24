
// Author: Pierce Brooks

#ifndef LS_PLAYER_HPP
#define LS_PLAYER_HPP

#include <LS/Ownable.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>

namespace LS
{
    class Game;

    class Player : public Ownable<Game*>
    {
        public:
            Player(Game* owner, const sf::Vector2u& position);
            virtual ~Player();
            bool shoot();
            void move(const sf::Vector2i& movement);
            Game* getOwner() const;
            sf::Sprite* getSprite() const;
            const sf::Vector2u& getPosition() const;
            void setPosition(const sf::Vector2u& position);
        private:
            Game* owner;
            sf::Texture* texture;
            sf::Sprite* sprite;
            sf::Vector2u position;
    };
}

#endif // LS_PLAYER_HPP
