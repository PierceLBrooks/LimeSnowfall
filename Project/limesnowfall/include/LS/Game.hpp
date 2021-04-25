
// Author: Pierce Brooks

#ifndef LS_GAME_HPP
#define LS_GAME_HPP

#include <vector>
#include <LS/Object.hpp>
#include <LS/Player.hpp>
#include <SFML3D/Graphics/RenderTexture.hpp>
#include <SFML3D/Graphics/RenderWindow.hpp>
#include <SFML3D/Graphics/Texture.hpp>
#include <SFML3D/Graphics/Sprite.hpp>
#include <SFML3D/Graphics/Image.hpp>
#include <SFML3D/Graphics/Camera.hpp>
#include <SFML3D/Graphics/Light.hpp>
#include <SFML3D/Graphics/Cuboid.hpp>
#include <SFML3D/Graphics/Billboard.hpp>

namespace LS
{
    class Game
    {
        public:
            enum Action
            {
                NONE,
                SHOOT,
                MOVE_LEFT,
                MOVE_RIGHT,
                PICKUP,
                DROP,
                JUMP,
                DIE
            };
            Game(sf3d::RenderWindow* output, const sf3d::Vector2u& size);
            virtual ~Game();
            bool act(Action action);
            bool playerShoot();
            bool playerMove(const sf3d::Vector2i& movement);
            bool playerPickup();
            bool playerDrop();
            bool playerJump();
            bool playerDie();
            bool update(sf3d::RenderTexture* window, float deltaTime);
            sf3d::RenderWindow* getWindow() const;
            Player* getPlayer() const;
            sf3d::Vector2f getPlayerPosition() const;
        protected:
            float pi;
            float turn;
            Player* player;
            sf3d::RenderWindow* output;
            sf3d::RenderTexture* window;
            sf3d::Camera* camera;
            sf3d::Light* light;
            sf3d::Light* cameraLight;
            sf3d::Cuboid* axisX;
            sf3d::Cuboid* axisY;
            sf3d::Cuboid* axisZ;
            sf3d::Billboard* frame;
            sf3d::RenderTexture* scene;
            sf3d::Cuboid* briefcase;
            sf3d::Cuboid* elevatorFloor;
            sf3d::Cuboid* elevatorWallLeft;
            sf3d::Cuboid* elevatorWallRight;
            sf3d::Cuboid* elevatorWallBack;
            Object* shaftBottom;
            Object* shaftTop;
            sf3d::View view;
    };
}

#endif // LS_GAME_HPP
