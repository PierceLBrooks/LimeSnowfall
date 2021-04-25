
// Author: Pierce Brooks

#include <LS/LimeSnowfall.hpp>
#include <iostream>
#include <SFML3D/Graphics/RenderTexture.hpp>
#include <SFML3D/Graphics/RenderWindow.hpp>
#include <SFML3D/Window/Event.hpp>
#include <SFML3D/Window/Mouse.hpp>
#include <SFML3D/Window/Keyboard.hpp>

typedef LS::LimeSnowfall Application;

int main(int argc, char** argv)
{
    sf3d::View view;
    float deltaTime;
    float reset;
    bool focus;
    Application* application;
    sf3d::Clock* clock = new sf3d::Clock();
    sf3d::RenderWindow* window = new sf3d::RenderWindow();
    sf3d::RenderTexture* output = new sf3d::RenderTexture();
    sf3d::Sprite* frame = new sf3d::Sprite();
    window->create(sf3d::VideoMode(1280, 720), "Lime Snowfall", sf3d::Style::None);
    window->setVerticalSyncEnabled(true);
    output->create(window->getSize().x, window->getSize().y, true);
    output->enableDepthTest(true);
    application = new Application(window);
    frame->setTexture(output->getTexture());
    view = window->getDefaultView();
    focus = true;
    reset = 0.0f;
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
                case sf3d::Event::GainedFocus:
                    focus = true;
                    break;
                case sf3d::Event::LostFocus:
                    focus = false;
                    break;
            }
        }
        window->clear(sf3d::Color::White);
        output->clear(sf3d::Color::Black);
        if (reset > 0.0f)
        {
            if (focus)
            {
                deltaTime = clock->restart().asSeconds();
                reset -= deltaTime;
                if (reset < 0.0f)
                {
                    reset = 0.0f;
                    application = new Application(window);
                }
                else
                {
                    output->display();
                    window->draw(*frame);
                    window->display();
                }
            }
            else
            {
                output->display();
                window->draw(*frame);
                window->display();
            }
        }
        else
        {
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
            if (focus)
            {
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
                    delete application;
                    application = nullptr;
                    reset = 2.5f;
                }
            }
            else
            {
                output->display();
                window->draw(*frame);
                window->display();
            }
        }
    }
    delete clock;
    delete output;
    delete frame;
    delete window;
    delete application;
    return 0;
}
