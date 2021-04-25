
// Author: Pierce Brooks

#include <SFML3D/Window/Mouse.hpp>
#include <LS/LimeSnowfall.hpp>
#include <LS/Game.hpp>
#include <iostream>

LS::Game::Game(sf3d::RenderWindow* output, const sf3d::Vector2u& size)
{
    sf3d::Vector2f center;

    pi = PI;
    this->output = output;
    window = nullptr;
    player = new Player(this);
    camera = new sf3d::Camera(75.0f, 0.001f, 1000.0f);

    enemySoundBuffers.push_back(new sf3d::SoundBuffer());
    enemySoundBuffers.back()->loadFromFile("./Assets/shots.wav");
    enemySoundBuffers.push_back(new sf3d::SoundBuffer());
    enemySoundBuffers.back()->loadFromFile("./Assets/specops_hurt.wav");
    enemySoundBuffers.push_back(new sf3d::SoundBuffer());
    enemySoundBuffers.back()->loadFromFile("./Assets/specops_die.wav");
    enemySoundBuffers.push_back(new sf3d::SoundBuffer());
    enemySoundBuffers.back()->loadFromFile("./Assets/rope.wav");

    enemyImageLeft = new sf3d::Image();
    enemyImageLeft->loadFromFile("./Assets/specops.png");
    enemyImageLeft->flipHorizontally();
    enemyImageRight = new sf3d::Image();
    enemyImageRight->loadFromFile("./Assets/specops.png");
    enemyTextureLeft = new sf3d::Texture();
    enemyTextureLeft->loadFromImage(*enemyImageLeft);
    enemyTextureRight = new sf3d::Texture();
    enemyTextureRight->loadFromImage(*enemyImageRight);

    light = new sf3d::Light();
    light->setColor(sf3d::Color::White);
    light->setAmbientIntensity(0.25f);
    light->setDiffuseIntensity(1.0f);
    light->setLinearAttenuation(0.2f);
    light->setQuadraticAttenuation(0.05f);
    light->setDirectional(true);
    light->setDirection(sf3d::Vector3f(0.0f, 0.0f, 1.0f));
    light->enable();
    torchLight = new sf3d::Light();
    torchLight->setColor(sf3d::Color::White);
    torchLight->setAmbientIntensity(0.0f);
    torchLight->setDiffuseIntensity(1.0f);
    torchLight->setLinearAttenuation(0.2f);
    torchLight->setQuadraticAttenuation(0.05f);
    torchLight->setDirectional(true);
    torchLight->setDirection(sf3d::Vector3f(0.0f, 0.0f, 1.0f));
    torchLight->enable();
    cameraLight = new sf3d::Light();
    cameraLight->setColor(sf3d::Color::White);
    cameraLight->setAmbientIntensity(0.1f);
    cameraLight->setDiffuseIntensity(1.0f);
    cameraLight->setLinearAttenuation(0.02f);
    cameraLight->setQuadraticAttenuation(0.005f);
    cameraLight->enable();
    lightLeft = new sf3d::Light();
    lightLeft->setColor(sf3d::Color::White);
    lightLeft->setAmbientIntensity(0.0f);
    lightLeft->setDiffuseIntensity(1.0f);
    lightLeft->setLinearAttenuation(0.02f);
    lightLeft->setQuadraticAttenuation(0.005f);
    lightLeft->enable();
    lightRight = new sf3d::Light();
    lightRight->setColor(sf3d::Color::White);
    lightRight->setAmbientIntensity(0.0f);
    lightRight->setDiffuseIntensity(1.0f);
    lightRight->setLinearAttenuation(0.02f);
    lightRight->setQuadraticAttenuation(0.005f);
    lightRight->enable();
    sf3d::Light::enableLighting();

    float aspectRatio = static_cast<float>(output->getSize().x) / static_cast<float>(output->getSize().y);
    sf3d::Vector3f downscaleFactor(1.0f / static_cast<float>(output->getSize().x) * aspectRatio, -1.0f / static_cast<float>(output->getSize().y), 1);

    camera->scale(1.0f / aspectRatio, 1.0f, 1.0f);
    camera->setPosition(sf3d::Vector3f(0.0f, 1.0f, 25.0f));
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
    shaftTop->setScale(15.0f, 15.0f, 15.0f);
    shaftTop->setPosition(0.0f, 0.0f, 5.0f);
    shaftBottom = new Object();
    shaftBottom->loadFromFile("./Assets/shaft.obj");
    shaftBottom->setRotation(0.0f, sf3d::Vector3f(0.0f, 1.0f, 0.0f));
    shaftBottom->setScale(15.0f, 15.0f, 15.0f);
    shaftBottom->setPosition(0.0f, 0.0f, 5.0f);

    soundCount = 0;
    life = 0.0f;
    spawnLast = 0.0f;
    spawn = 5.0f*pi;
    spawner = 0.0f;

    view = output->getDefaultView();

    light->setPosition(sf3d::Vector3f(0.0f, 0.0f, 5.0f));

    frame = new sf3d::Billboard();
    scene = new sf3d::RenderTexture();
    scene->create(output->getSize().x, output->getSize().y, false);
    scene->setView(view);
    center = sf3d::Vector2f(scene->getSize())*0.5f;
    frame->setTexture(scene->getTexture());
    //frame->setCamera(*camera);
    frame->setPosition(sf3d::Vector3f(center.x, center.y, 0.0f));
    frame->setOrigin(sf3d::Vector3f(center.x, center.y, 0.0f));

    briefcase = new sf3d::Cuboid();
    briefcase->setColor(sf3d::Color(64, 64, 64));
    briefcase->setPosition(light->getPosition());
    briefcase->setSize(sf3d::Vector3f(0.5f, 0.35f, 0.5f));
    briefcase->setOrigin(briefcase->getSize()*0.5f);
    briefcase->move(-camera->getDirection()*15.0f);
    briefcase->move(sf3d::Vector3f(0.0f, -0.8f, 0.0f));

    elevatorFloor = new sf3d::Cuboid();
    elevatorFloor->setColor(sf3d::Color(144, 144, 144));
    elevatorFloor->setPosition(light->getPosition());
    elevatorFloor->setSize(sf3d::Vector3f(30.0f, 1.0f, 100.0f));
    elevatorFloor->setOrigin(elevatorFloor->getSize()*0.5f);
    elevatorFloor->move(-camera->getDirection()*elevatorFloor->getSize().z*0.5f);
    elevatorFloor->move(elevatorFloor->getSize().x*0.5f, -10.0f, -elevatorFloor->getSize().z*0.1f);
    elevatorWallLeft = new sf3d::Cuboid();
    elevatorWallLeft->setColor(elevatorFloor->getColor());
    elevatorWallLeft->setPosition(light->getPosition());
    elevatorWallLeft->setSize(sf3d::Vector3f(1.0f, 3.0f, 100.0f));
    elevatorWallLeft->setOrigin(elevatorWallLeft->getSize()*0.5f);
    elevatorWallLeft->move(-camera->getDirection()*elevatorWallLeft->getSize().z*0.5f);
    elevatorWallLeft->move(-3.0f, elevatorWallLeft->getSize().y*0.5f, elevatorWallLeft->getSize().z*0.55f);
    elevatorWallRight = new sf3d::Cuboid();
    elevatorWallRight->setColor(elevatorFloor->getColor());
    elevatorWallRight->setPosition(light->getPosition());
    elevatorWallRight->setSize(sf3d::Vector3f(1.0f, 3.0f, 100.0f));
    elevatorWallRight->setOrigin(elevatorWallRight->getSize()*0.5f);
    elevatorWallRight->move(-camera->getDirection()*elevatorWallRight->getSize().z*0.5f);
    elevatorWallRight->move(4.0f, elevatorWallRight->getSize().y*0.5f, elevatorWallRight->getSize().z*0.55f);
    elevatorWallBack = new sf3d::Cuboid();
    elevatorWallBack->setColor(elevatorFloor->getColor());
    elevatorWallBack->setPosition(light->getPosition());
    elevatorWallBack->setSize(sf3d::Vector3f(100.0f, 3.0f, 1.0f));
    elevatorWallBack->setOrigin(elevatorWallBack->getSize()*0.5f);
    //elevatorWallBack->move(-camera->getDirection()*elevatorWallBack->getSize().z*0.5f);
    elevatorWallBack->move(elevatorWallBack->getSize().x*0.5f, elevatorWallBack->getSize().y*0.37f, elevatorWallBack->getSize().x*0.2f);
    elevatorWallBack->setColor(sf3d::Color(128, 128, 128));
    elevatorFloor->setColor(sf3d::Color::White);

    ballLeft = new sf3d::SphericalPolyhedron();
    ballLeft->setRadius(0.5f);
    ballLeft->setColor(sf3d::Color::White);
    ballLeft->setPosition(sf3d::Vector3f(-10.0f, 0.0f, 0.0f));
    ballRight = new sf3d::SphericalPolyhedron();
    ballRight->setRadius(0.5f);
    ballRight->setColor(sf3d::Color::White);
    ballRight->setPosition(sf3d::Vector3f(10.0f, 0.0f, 0.0f));
}

LS::Game::~Game()
{
    for (unsigned int i = 0; i != bullets.size(); ++i)
    {
        delete bullets[i];
    }
    bullets.clear();
    for (unsigned int i = 0; i != enemies.size(); ++i)
    {
        delete enemies[i];
    }
    enemies.clear();
    for (unsigned int i = 0; i != enemySoundBuffers.size(); ++i)
    {
        delete enemySoundBuffers[i];
    }
    enemySoundBuffers.clear();
    delete shaftTop;
    delete shaftBottom;
    delete axisX;
    delete axisY;
    delete axisZ;
    delete camera;
    delete cameraLight;
    delete torchLight;
    delete light;
    delete player;
    delete frame;
    delete scene;
    delete briefcase;
    delete elevatorFloor;
    delete elevatorWallLeft;
    delete elevatorWallRight;
    delete elevatorWallBack;
    delete ballLeft;
    delete ballRight;
    delete lightLeft;
    delete lightRight;
    delete enemyTextureLeft;
    delete enemyTextureRight;
    delete enemyImageLeft;
    delete enemyImageRight;
}

bool LS::Game::act(Action action)
{
    switch (action)
    {
    case SHOOT:
        return playerShoot();
    case MOVE_LEFT:
        return playerMove(sf3d::Vector2i(-1, 0));
    case MOVE_RIGHT:
        return playerMove(sf3d::Vector2i(1, 0));
    case PICKUP:
        return playerPickup();
    case DROP:
        return playerDrop();
    case JUMP:
        return playerJump();
    case DIE:
        return playerDie();
    }
    return false;
}

bool LS::Game::playerShoot()
{
    float angle = 0.0f;
    if (window == nullptr)
    {
        return false;
    }
    if (player->shoot(angle))
    {
        std::cout << "bullet" << std::endl;
        bullets.push_back(new Bullet(player, angle*(pi/180.0f)));
        return true;
    }
    return false;
}

bool LS::Game::playerMove(const sf3d::Vector2i& movement)
{
    player->go(movement);
    return true;
}

bool LS::Game::playerPickup()
{
    if (output == nullptr)
    {
        return false;
    }
    if (briefcase == nullptr)
    {
        return false;
    }
    if (fabsf(((player->getSprite()->getPosition().x-(0.5f*static_cast<float>(output->getSize().x)))/32.0f)-(briefcase->getPosition().x*4.0f)) > 4.0f)
    {
        return false;
    }
    if (!player->pickup())
    {
        return false;
    }
    delete briefcase;
    briefcase = nullptr;
    return true;
}

bool LS::Game::playerDrop()
{
    if (output == nullptr)
    {
        return false;
    }
    if (briefcase != nullptr)
    {
        return false;
    }
    if (!player->drop())
    {
        return false;
    }
    briefcase = new sf3d::Cuboid();
    briefcase->setColor(sf3d::Color(64, 64, 64));
    briefcase->setPosition(light->getPosition());
    briefcase->setSize(sf3d::Vector3f(0.5f, 0.35f, 0.5f));
    briefcase->setOrigin(briefcase->getSize()*0.5f);
    briefcase->move(-camera->getDirection()*15.0f);
    briefcase->move(sf3d::Vector3f((player->getSprite()->getPosition().x-(0.5f*static_cast<float>(output->getSize().x)))/480.0f, -0.8f, 0.0f));
    briefcase->setPosition(sf3d::Vector3f(briefcase->getPosition().x*4.0f, briefcase->getPosition().y, briefcase->getPosition().z));
    std::cout << briefcase->getPosition().x << std::endl;
    return true;
}

bool LS::Game::playerJump()
{
    return player->jump();
}

bool LS::Game::playerDie()
{
    if (output == nullptr)
    {
        return false;
    }
    std::cout << "die" << std::endl;
    return true;
}

bool LS::Game::playerHurt(Bullet* bullet)
{
    return player->hurt(bullet);
}

bool LS::Game::enemyShoot(Enemy* enemy, float angle)
{
    bullets.push_back(new Bullet(enemy, angle*(pi/180.0f)));
    return true;
}

bool LS::Game::countSound(int sounds)
{
    if (soundCount+sounds < 500)
    {
        soundCount += sounds;
        return true;
    }
    std::cout << "sound" << soundCount << std::endl;
    return false;
}

bool LS::Game::update(sf3d::RenderTexture* window, float deltaTime)
{
    if (output == nullptr)
    {
        return false;
    }

    float gravity = 250.0f;
    sf3d::Vector3f center = window->getView().getCenter();
    sf3d::Vector2f mouse = sf3d::Vector2f(sf3d::Mouse::getPosition(*output))+(sf3d::Vector2f(center.x, center.y)-(window->getView().getSize()*0.5f));

    life += deltaTime;
    spawner += deltaTime;
    if (spawner >= spawn)
    {
        float goal;
        float axis = sinf(life*pi)*0.8f;
        while (spawner >= spawn)
        {
            spawner -= spawn;
        }
        spawn += cosf(life*pi);
        while (spawn < 0.0f)
        {
            spawn += pi;
        }
        spawn /= sqrtf(life)/pi;
        spawn /= sqrtf(life-spawnLast);
        while (spawn > 15.0f)
        {
            spawn *= 0.5f;
        }
        std::cout << "spawn" << axis << std::endl;
        goal = static_cast<float>(output->getSize().y)*0.5f;
        goal -= fabsf(cosf(((life*pi)+pi)*0.75f))*goal*0.75f;
        axis *= static_cast<float>(output->getSize().x)*0.5f;
        axis += static_cast<float>(output->getSize().x)*0.5f;
        if (enemies.empty())
        {
            spawnLast = life;
            if (sinf(life*pi) > 0.0f)
            {
                enemies.push_back(new Enemy(this, enemyTextureLeft, axis, goal, -1, player->getScale(), enemySoundBuffers));
            }
            else
            {
                enemies.push_back(new Enemy(this, enemyTextureRight, axis, goal, 1, player->getScale(), enemySoundBuffers));
            }
        }
        else
        {
            if ((enemies.size() < 15) && (fabsf(enemies.back()->getPosition().x-axis) > static_cast<float>(player->getSprite()->getTextureRect().width)))
            {
                spawnLast = life;
                if (sinf(life*pi) > 0.0f)
                {
                    enemies.push_back(new Enemy(this, enemyTextureLeft, axis, goal, -1, player->getScale(), enemySoundBuffers));
                }
                else
                {
                    enemies.push_back(new Enemy(this, enemyTextureRight, axis, goal, 1, player->getScale(), enemySoundBuffers));
                }
            }
        }
    }

    this->window = window;

    window->setView(*camera);

    ballLeft->move(sf3d::Vector3f(0.0f, deltaTime*gravity, 0.0f));
    ballRight->move(sf3d::Vector3f(0.0f, deltaTime*gravity, 0.0f));
    if (ballLeft->getPosition().y > gravity)
    {
        ballLeft->setPosition(sf3d::Vector3f(ballLeft->getPosition().x, -ballLeft->getPosition().y, ballLeft->getPosition().z));
        ballRight->setPosition(sf3d::Vector3f(ballRight->getPosition().x, -ballRight->getPosition().y, ballRight->getPosition().z));
    }
    cameraLight->setPosition(camera->getPosition());
    lightLeft->setPosition(ballLeft->getPosition());
    lightRight->setPosition(ballRight->getPosition());
    if ((!player->getBriefcase()) && (!player->getAirborne()))
    {
        float torch = (player->getSprite()->getPosition().x-(0.5f*static_cast<float>(output->getSize().x)))/32.0f;
        torchLight->setPosition(light->getPosition());
        torchLight->move(sf3d::Vector3f(torch, 0.0f, 0.0f));
        torchLight->setDirection(sf3d::Vector3f((player->getFacing()>0)?1.0f:-1.0f, 0.0f, 0.0f));
        if (!torchLight->isEnabled())
        {
            torchLight->enable();
        }
    }
    else
    {
        if (torchLight->isEnabled())
        {
            torchLight->disable();
        }
    }

    /*
    window->draw(*axisX);
    window->draw(*axisY);
    window->draw(*axisZ);
    */

    window->draw(*shaftTop);
    window->draw(*shaftBottom);

    window->draw(*ballLeft);
    window->draw(*ballRight);

    window->draw(*elevatorWallBack);
    window->draw(*elevatorFloor);
    window->draw(*elevatorWallLeft);
    window->draw(*elevatorWallRight);

    if (briefcase != nullptr)
    {
        window->draw(*briefcase);
    }

    //light->disable();
    sf3d::Light::disableLighting();
    window->enableDepthTest(false);
    window->setView(view);
    scene->setView(view);
    scene->clear(sf3d::Color::Transparent);
    for (int i = 0; i != bullets.size(); ++i)
    {
        if (!bullets[i]->update(scene, deltaTime))
        {
            std::cout << "expire" << std::endl;
            bullets.erase(bullets.begin()+i);
            --i;
            continue;
        }
        if (bullets[i]->getOwner() != player)
        {
            if (playerHurt(bullets[i]))
            {
                std::cout << "hurt" << std::endl;
                bullets.erase(bullets.begin()+i);
                --i;
                continue;
            }
            continue;
        }
        for (int j = 0; j != enemies.size(); ++j)
        {
            if (enemies[j]->hurt(bullets[i]))
            {
                std::cout << "shot" << std::endl;
                bullets.erase(bullets.begin()+i);
                --i;
                break;
            }
        }
    }
    for (int i = 0; i != enemies.size(); ++i)
    {
        if (!enemies[i]->update(scene, deltaTime, player))
        {
            std::cout << "kill" << std::endl;
            enemies.erase(enemies.begin()+i);
            --i;
            continue;
        }
    }
    if (!player->update(scene, deltaTime, mouse))
    {
        return false;
    }
    scene->display();
    //frame->setPosition(camera->getPosition());
    //frame->move(camera->getDirection()*deltaTime);
    //frame->move(0.0f, -deltaTime, 0.0f);
    //frame->setRotation(-turn, sf3d::Vector3f(0.0f, 0.0f, 1.0f));
    sf3d::Light::enableLighting();
    window->enableDepthTest(true);
    //light->enable();
    //window->setView(*camera);
    window->draw(*frame);
    return true;
}

LS::Player* LS::Game::getPlayer() const
{
    return player;
}

sf3d::RenderWindow* LS::Game::getWindow() const
{
    return output;
}
