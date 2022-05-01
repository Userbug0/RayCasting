#pragma once

#include <SFML/Graphics.hpp>

#include "Grid.h"
#include "LightSource.h"


class MainApp
{
public:
	MainApp();
	~MainApp();

	void Start();

private:
	void gameLoop();
	void handleEvents();
	void render();
	void update(const sf::Time& frameTime);

	void initWalls();

	bool m_running;
	sf::RenderWindow* m_Window;
	Grid* m_Grid;
	LightSource* m_Player;
};

