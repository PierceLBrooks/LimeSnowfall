
// Author: Pierce Brooks

#include <LS/LimeSnowfall.hpp>
#include <iostream>
#include <SFML3D/Graphics/RenderTexture.hpp>
#include <SFML3D/Graphics/RenderWindow.hpp>
#include <SFML3D/Window/Event.hpp>
#include <SFML3D/Window/Mouse.hpp>
#include <SFML3D/Window/Keyboard.hpp>

typedef LS::LimeSnowfall Application;

void report(const sf3d::Vector2f& target)
{
    std::cout << target.x << "  " << target.y << std::endl;
}

int main(int argc, char** argv)
{
    sf3d::Vector2f center;
    float deltaTime;
    sf3d::Clock* clock = new sf3d::Clock();
    sf3d::RenderWindow* window = new sf3d::RenderWindow();
    sf3d::RenderTexture* output = new sf3d::RenderTexture();
    Application* application = new Application(window);
    auto resolutions = sf3d::VideoMode::getFullscreenModes();
    window->create(resolutions[resolutions.size()/2], "Lime Snowfall");
    output->create(window->getSize().x, window->getSize().y);
    clock->restart();
    while (window->isOpen())
    {
        sf3d::Event event;
        while (window->pollEvent(event))
        {
            switch (event.type)
            {
                case sf3d::Event::Closed:
                    window->close();
                    break;
            }
        }
        //report(center);
        window->clear(sf3d::Color::Black);
        window->setView(sf3d::View(center, sf3d::Vector2f(window->getSize())));
        if (sf3d::Mouse::isButtonPressed(sf3d::Mouse::Button::Left))
        {
            application->act(LS::Game::Action::SHOOT);
        }
        deltaTime = clock->restart().asSeconds();
        application->update(output, deltaTime);
        window->display();
        if (sf3d::Keyboard::isKeyPressed(sf3d::Keyboard::Key::Escape))
        {
            window->close();
        }
    }
    delete clock;
    delete window;
    delete application;
    return 0;
}
