#pragma once

#include <SFML/Graphics.hpp>

#include "Vector2.h"


class Grid
{
public:
	struct Cell;

public:
	Grid(const Vector2& position, size_t cellSize);

	void Draw(sf::RenderWindow* window);

	size_t GetWidth()     const	{ return m_width; }
	size_t GetHeight()    const	{ return m_height; }
	size_t GetSize()      const	{ return m_height * m_width; }
	Vector2 GetPosition() const { return m_position; }

	Cell& GetCell(size_t index)			    { return cells[index]; }
	const Cell& GetCell(size_t index) const { return cells[index]; }
	size_t GetCellSize()			  const { return m_cellSize; }
	void SetCellColor(size_t index, const sf::Color& color);

	Vector2 IndexToWorld(size_t index) const;
	size_t  WorldToIndex(const Vector2& position) const;
	Vector2 WorldToGrid(const Vector2& position) const;

	enum class CellType { Default, Wall };

	void SetType(size_t index, const CellType& type) { cells[index].type = type; }
	CellType GetType(size_t index) const             { return cells[index].type; }

	struct Cell
	{
		CellType type = CellType::Default;
		sf::Color color = Grid::DefaultColor;
	};

	static constexpr const sf::Color& DefaultColor = sf::Color::White;
	static constexpr const sf::Color& DefaultOutlineColor = sf::Color::Black;
	static constexpr const sf::Color& WallColor = sf::Color::Black;
	static constexpr const sf::Color& OutlineWallColor = sf::Color::White;


private:
	std::vector<Cell> cells;
	size_t m_cellSize;

	Vector2 m_position;
	size_t m_width;
	size_t m_height;
};
