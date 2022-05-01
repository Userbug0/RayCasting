#include "MainApp.hpp"


MainApp::MainApp()
{
    LightEngine = new Engine("RayCasting", {0, 0, 0});

    InitWalls();
}


void MainApp::InitWalls()
{
    // Box
    LightEngine->AddWall(new LineSegment({ 0, 0 }, { WIDTH, 0 }, 4, { 0, 250, 250 }));
    LightEngine->AddWall(new LineSegment({ WIDTH, HEIGHT }, { 0, HEIGHT }, 4, {0, 250, 250}));
    LightEngine->AddWall(new LineSegment({ WIDTH, 0 }, { WIDTH, HEIGHT }, 4, {0, 250, 250}));
    LightEngine->AddWall(new LineSegment({ 0, HEIGHT }, { 0, 0 }, 4, {0, 250, 250}));

    Vector2d point1;
    Vector2d point2;
    for (int i = 0; i < 6; ++i)
    {
        point1 = { (float)(std::rand() % WIDTH) , (float)(std::rand() % HEIGHT) };
        point2 = { (float)(std::rand() % WIDTH) , (float)(std::rand() % HEIGHT) };
        LightEngine->AddWall(new LineSegment(point1, point2, 4, { 0, 250, 250 }));
    }
}


void MainApp::Start()
{
    sf::Clock clock;

    LightEngine->Start();

    clock.restart();
    while(LightEngine->isRunning())
    {
        LightEngine->HandleEvent();
        LightEngine->Update(clock.getElapsedTime());
        clock.restart();

        LightEngine->Render();
    }
}


MainApp::~MainApp()
{
    delete LightEngine;
}
