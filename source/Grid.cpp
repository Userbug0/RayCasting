#include "Grid.h"
#include "Settings.h"


const sf::Color Grid::DefaultColor = sf::Color::White;
const sf::Color Grid::DefaultOutlineColor = sf::Color::Black;
const sf::Color Grid::WallColor = sf::Color::Black;
const sf::Color Grid::OutlineWallColor = sf::Color::White;


Grid::Grid(size_t cellSize)
	: m_cellSize(cellSize)
{
	m_width = WINDOW_WIDTH / m_cellSize;
	m_height = WINDOW_HEIGHT / m_cellSize;

	for (size_t i = 0; i < m_width * m_height; ++i)
		cells.push_back(Cell());
}


void Grid::Draw(sf::RenderWindow* window)
{
	window->clear(DefaultColor);

	sf::Vertex line[2] = { sf::Vertex({0, 0}, DefaultOutlineColor), 
						   sf::Vertex({0, WINDOW_HEIGHT}, DefaultOutlineColor) };

	for (size_t i = 0; i < m_width; ++i)
	{
		window->draw(line, 2, sf::Lines);

		line[0].position += { (float)m_cellSize, 0 };
		line[1].position += { (float)m_cellSize, 0 };
	}

	line[0].position = { 0, 0 };
	line[1].position = { WINDOW_WIDTH, 0};
	for (size_t i = 0; i < m_height; ++i)
	{
		window->draw(line, 2, sf::Lines);

		line[0].position += { 0, (float)m_cellSize };
		line[1].position += { 0, (float)m_cellSize };
	}

	sf::RectangleShape rect({ (float)m_cellSize, (float)m_cellSize});
	rect.setOutlineColor(OutlineWallColor);
	rect.setOutlineThickness(1);

	for (size_t i = 0; i < cells.size(); ++i)
	{
		if (cells[i].color != DefaultColor)
		{
			rect.setFillColor(cells[i].color);
			Vector2 pos = IndexToWorld(i);
			rect.setPosition({ pos.x, pos.y });
			window->draw(rect);
		}

		else if (cells[i].type == CellType::Wall)
		{
			rect.setFillColor(WallColor);
			Vector2 pos = IndexToWorld(i);
			rect.setPosition({pos.x, pos.y});
			window->draw(rect);
		}

	}
}


void Grid::SetCellColor(size_t index, const sf::Color& color)
{
	cells[index].color = color;
}


Vector2 Grid::IndexToWorld(size_t index) const
{
	float x = index % m_width * (float)m_cellSize;
	float y = (index / m_width) % m_height * (float)m_cellSize;
	return Vector2(x, y);
}


Vector2 Grid::WorldToGrid(const Vector2& position) const
{
	float x = position.x / m_width * (float)m_cellSize;
	float y = position.y / m_height * (float)m_cellSize;
	return Vector2(x, y);
}


size_t Grid::WorldToIndex(const Vector2& position) const
{
	return (int)position.x / m_cellSize % m_width + (int)position.y / m_cellSize * m_width;
}
