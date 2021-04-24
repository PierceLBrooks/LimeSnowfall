
// Author: Pierce Brooks

#ifndef LS_GAME_HPP
#define LS_GAME_HPP

#include <vector>
#include <LS/Player.hpp>
#include <SFML3D/Graphics/RenderTexture.hpp>
#include <SFML3D/Graphics/RenderWindow.hpp>
#include <SFML3D/Graphics/Texture.hpp>
#include <SFML3D/Graphics/Sprite.hpp>
#include <SFML3D/Graphics/Image.hpp>

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
            Game(sf3d::RenderWindow* output, const sf3d::Vector2u& size);
            virtual ~Game();
            bool act(Action action);
            bool shoot();
            bool movePlayer(const sf3d::Vector2i& movement);
            void update(sf3d::RenderTexture* window, float deltaTime);
            Player* getPlayer() const;
            sf3d::Vector2f getPlayerPosition() const;
        protected:
            float pi;
            float turn;
            int floor;
            unsigned int room;
            unsigned int score;
            Player* player;
            sf3d::RenderWindow* output;
            sf3d::RenderTexture* window;
    };
}

#endif // LS_GAME_HPP
