#pragma once

#include <SFML/Graphics.hpp>

#include "LightSource.hpp"
#include "LineSegment.hpp"
#include "Vector2d.hpp"
#include "Settings.hpp"


class Engine
{
public:
    Engine(const char* title, const sf::Color& clr);
    ~Engine();
    void Start();

    void AddWall(LineSegment* wall) {Walls.push_back(wall);}

    void Update(const sf::Time& FrameTime);
    void HandleEvent();
    void Render();

    bool isRunning(){return Running;}

private:
    void onKeyPress(const sf::Keyboard::Key& keycode);
    void onKeyRelease(const sf::Keyboard::Key& keycode);
    void onMouseMove(const Vector2d& mouse_pos);

    sf::RenderWindow* Window;

    LightSource* Lamp;
    std::vector<LineSegment*> Walls;

    sf::Color BackgroundColor;
    bool Running;
};

