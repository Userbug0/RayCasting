#pragma once

#include <SFML/Graphics.hpp>

#include "Vector2d.hpp"
#include "Settings.hpp"
#include "Engine.hpp"
#include "LineSegment.hpp"


class MainApp
{
public:
    MainApp();
    ~MainApp();

    void Start();

private:
    Engine* LightEngine;

    void InitWalls();
};

