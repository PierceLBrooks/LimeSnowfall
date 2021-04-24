
// Author: Pierce Brooks

#include <LS/LimeSnowfall.hpp>
#include <iostream>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Window/Keyboard.hpp>

typedef LS::LimeSnowfall Application;

void report(const sf::Vector2f& target)
{
    std::cout << target.x << "  " << target.y << std::endl;
}

int main(int argc, char** argv)
{
    sf::Vector2f center;
    float deltaTime;
    Application* application = new Application();
    sf::Clock* clock = new sf::Clock();
    sf::RenderWindow* window = new sf::RenderWindow();
    auto resolutions = sf::VideoMode::getFullscreenModes();
    window->create(resolutions[resolutions.size()/2], "Lime Snowfall");
    clock->restart();
    while (window->isOpen())
    {
        sf::Event event;
        while (window->pollEvent(event))
        {
            switch (event.type)
            {
                case sf::Event::Closed:
                    window->close();
                    break;
            }
        }
        //report(center);
        window->clear(sf::Color::Black);
        window->setView(sf::View(center, sf::Vector2f(window->getSize())));
        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
        {
            application->act(LS::Game::Action::SHOOT);
        }
        deltaTime = clock->restart().asSeconds();
        application->update(window, deltaTime, sf::Keyboard::isKeyPressed(sf::Keyboard::Key::M));
        window->display();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
        {
            window->close();
        }
    }
    delete clock;
    delete window;
    delete application;
    return 0;
}
