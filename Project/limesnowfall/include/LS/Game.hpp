
// Author: Pierce Brooks

#ifndef LS_GAME_HPP
#define LS_GAME_HPP

#include <vector>
#include <LS/Player.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Image.hpp>

namespace LS
{
    class Game
    {
        public:
            enum Action
            {
                NONE,
                SHOOT
            };
            Game(const sf::Vector2u& size);
            virtual ~Game();
            bool act(Action action);
            bool shoot();
            bool movePlayer(const sf::Vector2i& movement);
            void update(sf::RenderWindow* window, float deltaTime, bool mapView);
            Player* getPlayer() const;
            sf::Vector2f getPlayerPosition() const;
        protected:
            float pi;
            float turn;
            int floor;
            unsigned int room;
            unsigned int score;
            Player* player;
            sf::RenderWindow* window;
    };
}

#endif // LS_GAME_HPP
