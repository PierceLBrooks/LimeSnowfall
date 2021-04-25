
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
    Application* application;
    sf3d::Clock* clock = new sf3d::Clock();
    sf3d::RenderWindow* window = new sf3d::RenderWindow();
    sf3d::RenderTexture* output = new sf3d::RenderTexture();
    sf3d::Sprite* frame = new sf3d::Sprite();
    auto resolutions = sf3d::VideoMode::getFullscreenModes();
    window->create(resolutions[resolutions.size()/2], "Lime Snowfall");
    window->setVerticalSyncEnabled(true);
    output->create(window->getSize().x, window->getSize().y, true);
    output->enableDepthTest(true);
    application = new Application(window);
    frame->setTexture(output->getTexture());
    clock->restart();
    sf3d::View view = window->getDefaultView();
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
        window->clear(sf3d::Color::White);
        output->clear(sf3d::Color::Black);
        //window->setView(sf3d::View(center, sf3d::Vector2f(window->getSize())));
        if (sf3d::Mouse::isButtonPressed(sf3d::Mouse::Button::Left))
        {
            application->act(LS::Game::Action::SHOOT);
        }
        if (sf3d::Keyboard::isKeyPressed(sf3d::Keyboard::Key::Space))
        {
            application->act(LS::Game::Action::JUMP);
        }
        if (sf3d::Keyboard::isKeyPressed(sf3d::Keyboard::Key::E))
        {
            application->act(LS::Game::Action::PICKUP);
        }
        if (sf3d::Keyboard::isKeyPressed(sf3d::Keyboard::Key::F))
        {
            application->act(LS::Game::Action::DROP);
        }
        if (sf3d::Keyboard::isKeyPressed(sf3d::Keyboard::Key::A))
        {
            application->act(LS::Game::Action::MOVE_LEFT);
        }
        if (sf3d::Keyboard::isKeyPressed(sf3d::Keyboard::Key::D))
        {
            application->act(LS::Game::Action::MOVE_RIGHT);
        }
        deltaTime = clock->restart().asSeconds();
        output->setView(view);
        if (application->update(output, deltaTime))
        {
            output->display();
            window->draw(*frame);
            window->display();
            if (sf3d::Keyboard::isKeyPressed(sf3d::Keyboard::Key::Escape))
            {
                window->close();
            }
        }
        else
        {
            output->display();
            window->draw(*frame);
            window->display();
            window->close();
        }
    }
    delete clock;
    delete output;
    delete frame;
    delete window;
    delete application;
    return 0;
}
