
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
    sf3d::View view;
    sf3d::Vector2f center;
    float deltaTime;
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
                window->close();
            }
        }
        else
        {
            output->display();
            window->draw(*frame);
            window->display();
        }
    }
    delete clock;
    delete output;
    delete frame;
    delete window;
    delete application;
    return 0;
}
