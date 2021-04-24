
// Author: Pierce Brooks

#ifndef LS_HPP
#define LS_HPP

#include <LS/Game.hpp>
#include <SFML3D/Graphics/RenderWindow.hpp>

namespace LS
{
    class LimeSnowfall : public Game
    {
        public:
            LimeSnowfall(sf3d::RenderWindow* output);
            virtual ~LimeSnowfall();
    };
}

#endif // LS_HPP
