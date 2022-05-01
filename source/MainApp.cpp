#include "MainApp.h"
#include "Settings.h"


MainApp::MainApp()
	: m_running(false)
{
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;

	m_Window = new sf::RenderWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "DDA", sf::Style::Close, settings);
	m_Window->setFramerateLimit(FPS);

	m_Grid = new Grid(50);
	initWalls();

	m_Player = new LightSource(200, M_PI / 2, 50, WINDOW_HEIGHT / 2);
}


void MainApp::Start()
{
	m_running = true;
	gameLoop();
}


void MainApp::gameLoop()
{
	sf::Clock clock;

	while (m_running)
	{
		handleEvents();
		render();
		update(clock.getElapsedTime());

		clock.restart();
	}
}


void MainApp::handleEvents()
{
	sf::Event event;

	while (m_Window->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			m_running = false;

		if (event.type == sf::Event::KeyPressed)
			m_Player->OnKeyPressed(event.key.code);

		if (event.type == sf::Event::KeyReleased)
			m_Player->OnKeyReleased(event.key.code);

		if (event.type == sf::Event::MouseMoved)
		{
			sf::Vector2i mpos = sf::Mouse::getPosition(*m_Window);
			m_Player->LookAt({ (float)mpos.x, (float)mpos.y });
		}

	}
}


void MainApp::render()
{
	m_Grid->Draw(m_Window);
	m_Player->Draw(m_Window, m_Grid);

	m_Window->display();
}


void MainApp::update(const sf::Time& frameTime)
{
	m_Player->Move(frameTime.asSeconds(), m_Grid);
}


void MainApp::initWalls()
{
	size_t gwidth = m_Grid->GetWidth();
	size_t size = m_Grid->GetHeight() * gwidth;

	for (size_t i = 0; i < gwidth; ++i)
		m_Grid->SetType(i, Grid::CellType::Wall);

	for (size_t i = size - gwidth; i < size; ++i)
		m_Grid->SetType(i, Grid::CellType::Wall);

	for (size_t i = gwidth; i < size; i += gwidth)
		m_Grid->SetType(i, Grid::CellType::Wall);

	for (size_t i = gwidth - 1; i < size; i += gwidth)
		m_Grid->SetType(i, Grid::CellType::Wall);

	m_Grid->SetType(6 + gwidth, Grid::CellType::Wall);
	m_Grid->SetType(6 + 2 * gwidth, Grid::CellType::Wall);
	m_Grid->SetType(6 + 3 * gwidth, Grid::CellType::Wall);
	m_Grid->SetType(6 + 3 * gwidth - 1, Grid::CellType::Wall);
	m_Grid->SetType(6 + 3 * gwidth - 2, Grid::CellType::Wall);

	m_Grid->SetType(8 * gwidth - 2, Grid::CellType::Wall);
	m_Grid->SetType(8 * gwidth - 3, Grid::CellType::Wall);
	m_Grid->SetType(8 * gwidth - 4, Grid::CellType::Wall);
	m_Grid->SetType(8 * gwidth - 5, Grid::CellType::Wall);

	m_Grid->SetType(size - 2 * gwidth + 4, Grid::CellType::Wall);
	m_Grid->SetType(size - 3 * gwidth + 4, Grid::CellType::Wall);
	m_Grid->SetType(size - 4 * gwidth + 4, Grid::CellType::Wall);
}


MainApp::~MainApp()
{
	delete m_Player;
	delete m_Grid;
	delete m_Window;
}
