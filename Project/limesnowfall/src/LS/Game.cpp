
// Author: Pierce Brooks

#include <SFML3D/Window/Mouse.hpp>
#include <LS/LimeSnowfall.hpp>
#include <LS/Game.hpp>
#include <iostream>

#define PI (22.0f/7.0f)

LS::Game::Game(sf3d::RenderWindow* output, const sf3d::Vector2u& size)
{
    sf3d::Vector2f center;

    pi = PI;
    this->output = output;
    window = nullptr;
    player = new Player(this);
    camera = new sf3d::Camera(75.0f, 0.001f, 1000.0f);

    light = new sf3d::Light();
    light->setColor(sf3d::Color::White);
    light->setAmbientIntensity(0.5f);
    light->setDiffuseIntensity(1.0f);
    light->setLinearAttenuation(0.2f);
    light->setQuadraticAttenuation(0.05f);
    //light->setDirectional(true);
    //light->setDirection(sf3d::Vector3f(0.0f, 0.0f, 1.0f));
    light->enable();
    sf3d::Light::enableLighting();

    float aspectRatio = static_cast<float>(output->getSize().x) / static_cast<float>(output->getSize().y);
    sf3d::Vector3f downscaleFactor(1.0f / static_cast<float>(output->getSize().x) * aspectRatio, -1.0f / static_cast<float>(output->getSize().y), 1);

    camera->scale(1.0f / aspectRatio, 1.0f, 1.0f);
    camera->setPosition(sf3d::Vector3f(0.0f, 0.0f, 25.0f));
    //camera->setDirection(sf3d::Vector3f(sqrtf(2.0f)*0.5f, 0.0f, sqrtf(2.0f)*0.5f));
    camera->setDirection(sf3d::Vector3f(0.0f, 0.0f, -1.0f));
    camera->setUpVector(sf3d::Vector3f(0.0f, 1.0f, 0.0f));

    axisX = new sf3d::Cuboid();
    axisX->setSize(sf3d::Vector3f(500.0f, 2.0f, 2.0f));
    axisX->setColor(sf3d::Color::Red);
    axisX->setPosition(0.0f, 0.0f, 0.0f);
    axisX->setOrigin(-250.0f, 1.0f, 1.0f);

    axisY = new sf3d::Cuboid();
    axisY->setSize(sf3d::Vector3f(2.0f, 500.0f, 2.0f));
    axisY->setColor(sf3d::Color::Green);
    axisY->setPosition(0.0f, 0.0f, 0.0f);
    axisY->setOrigin(1.0f, -250.0f, 1.0f);

    axisZ = new sf3d::Cuboid();
    axisZ->setSize(sf3d::Vector3f(2.0f, 2.0f, 500.0f));
    axisZ->setColor(sf3d::Color::Blue);
    axisZ->setPosition(0.0f, 0.0f, 0.0f);
    axisZ->setOrigin(1.0f, 1.0f, -250.0f);

    shaftTop = new Object();
    shaftTop->loadFromFile("./Assets/shaft.obj");
    shaftTop->setRotation(180.0f, sf3d::Vector3f(0.0f, 0.0f, 1.0f));
    shaftTop->setScale(10.0f, 10.0f, 10.0f);
    shaftTop->setPosition(0.0f, 0.0f, 5.0f);
    shaftBottom = new Object();
    shaftBottom->loadFromFile("./Assets/shaft.obj");
    shaftBottom->setRotation(0.0f, sf3d::Vector3f(0.0f, 1.0f, 0.0f));
    shaftBottom->setScale(10.0f, 10.0f, 10.0f);
    shaftBottom->setPosition(0.0f, 0.0f, 5.0f);

    turn = 1.0f;

    view = output->getDefaultView();

    light->setPosition(sf3d::Vector3f());

    frame = new sf3d::Billboard();
    scene = new sf3d::RenderTexture();
    scene->create(output->getSize().x, output->getSize().y, false);
    scene->setView(view);
    center = sf3d::Vector2f(scene->getSize())*0.5f;
    frame->setTexture(scene->getTexture());
    //frame->setCamera(*camera);
    frame->setPosition(sf3d::Vector3f(center.x, center.y, 0.0f));
    frame->setOrigin(sf3d::Vector3f(center.x, center.y, 0.0f));
}

LS::Game::~Game()
{
    delete shaftTop;
    delete shaftBottom;
    delete axisX;
    delete axisY;
    delete axisZ;
    delete camera;
    delete light;
    delete player;
    delete frame;
    delete scene;
}

bool LS::Game::act(Action action)
{
    switch (action)
    {
    case SHOOT:
        return shoot();
    case MOVE_LEFT:
        return movePlayer(sf3d::Vector2i(-1, 0));
    case MOVE_RIGHT:
        return movePlayer(sf3d::Vector2i(1, 0));
    }
    return false;
}

bool LS::Game::shoot()
{
    if (window == nullptr)
    {
        return false;
    }
    if (player->shoot())
    {
        sf3d::Vector3f center = window->getView().getCenter();
        sf3d::Color color = sf3d::Color::White;
        sf3d::Vector2f mouse = sf3d::Vector2f(sf3d::Mouse::getPosition(*output))+(sf3d::Vector2f(center.x, center.y)-(window->getView().getSize()*0.5f));
        return true;
    }
    return false;
}

bool LS::Game::movePlayer(const sf3d::Vector2i& movement)
{
    player->move(movement);
    return true;
}

void LS::Game::update(sf3d::RenderTexture* window, float deltaTime)
{
    turn += deltaTime;

    //shaftTop->setScale(turn, turn, turn);
    //shaftBottom->setScale(turn, turn, turn);

    this->window = window;

    window->setView(*camera);

    /*
    window->draw(*axisX);
    window->draw(*axisY);
    window->draw(*axisZ);
    */

    window->draw(*shaftTop);
    window->draw(*shaftBottom);

    //light->disable();
    sf3d::Light::disableLighting();
    window->setView(view);
    scene->setView(view);
    scene->clear(sf3d::Color::Transparent);
    player->update(scene, deltaTime);
    scene->display();
    //frame->setPosition(camera->getPosition());
    //frame->move(camera->getDirection()*deltaTime);
    //frame->move(0.0f, -deltaTime, 0.0f);
    //frame->setScale(turn, turn, turn);
    frame->setRotation(-turn, sf3d::Vector3f(0.0f, 0.0f, 1.0f));
    sf3d::Light::enableLighting();
    //light->enable();
    //window->setView(*camera);
    window->draw(*frame);
}

LS::Player* LS::Game::getPlayer() const
{
    return player;
}

sf3d::RenderWindow* LS::Game::getWindow() const
{
    return output;
}
