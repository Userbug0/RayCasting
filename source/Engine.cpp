#include "Engine.hpp"


Engine::Engine(const char* title, const sf::Color& color):
    BackgroundColor(color), Running(true)
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    Window = new sf::RenderWindow(sf::VideoMode(WIDTH, HEIGHT), title, sf::Style::Close, settings);
    Window->setFramerateLimit(FPS);

    Lamp = new LightSource({WIDTH / 2, HEIGHT / 2}, {WIDTH / 2, 0.f}, (float)FIELD_OF_VIEW, DENSITY_OF_LIGHT);
}


void Engine::Start()
{
    Render();
}


void Engine::Update(const sf::Time& FrameTime)
{
    Lamp->MoveWithCollision(FrameTime, Walls);
}


void Engine::Render()
{
    Window->clear(BackgroundColor);

    Lamp->Draw(Window, Walls);

    for(auto& wall: Walls)
        wall->Draw(Window);

    Window->display();
}


void Engine::HandleEvent()
{
    sf::Event event;

    while (Window->pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            Running = false;

        else if (event.type == sf::Event::KeyPressed)
            onKeyPress(event.key.code);

        else if (event.type == sf::Event::KeyReleased)
            onKeyRelease(event.key.code);

        else if (event.type == sf::Event::MouseMoved) 
        {
            sf::Vector2i mpos = sf::Mouse::getPosition(*Window);
            onMouseMove({ (float)mpos.x, (float)mpos.y });
        }
    }
}


inline void Engine::onMouseMove(const Vector2d& mouse_pos)
{
    Lamp->LookAt(mouse_pos);
}


inline void Engine::onKeyRelease(const sf::Keyboard::Key& keycode)
{
    Lamp->setDirection({ 0, 0 });
}


void Engine::onKeyPress(const sf::Keyboard::Key& keycode)
{
    if (keycode == sf::Keyboard::A)
        Lamp->setDirection({ -1, 0 });
    else if (keycode == sf::Keyboard::W)
        Lamp->setDirection({ 0, -1 });
    else if (keycode == sf::Keyboard::D)
        Lamp->setDirection({ 1, 0 });
    else if (keycode == sf::Keyboard::S)
        Lamp->setDirection({ 0, 1 });
}


Engine::~Engine()
{
    for(auto& wall: Walls){
        delete wall;
    }

    delete Lamp;
    delete Window;
}
