#include "MovAble.h"


MovAble::MovAble(float speed, const Vector2& position)
	: m_radius(7), m_direction(0, 0), m_position(position), m_speed(speed)
{
	m_toDraw.setRadius(m_radius);
	m_toDraw.setFillColor(sf::Color::Green);
	m_toDraw.setPosition({ m_position.x - m_radius, m_position.y - m_radius });
}


void MovAble::Draw(sf::RenderWindow* window)
{
	m_toDraw.setPosition({ m_position.x - m_radius, m_position.y - m_radius });

	window->draw(m_toDraw);
}


Vector2 MovAble::GetPosition() const
{
	return m_position;
}


void MovAble::Move(float frameTime, Grid* grid)
{
	m_position += m_direction * m_speed * frameTime;

	size_t cellSize = grid->GetCellSize();
	size_t myIndex = grid->WorldToIndex(m_position);

	Vector2 cell;
	float dist;

	if (myIndex - 1 >= 0 && grid->GetType(myIndex - 1) == Grid::CellType::Wall)
	{
		Vector2 cell = grid->IndexToWorld(myIndex - 1);
		float dist = m_position.x - m_radius - cell.x - cellSize;
		if (dist < 0)
			m_position.x -= dist;
	}

	if (myIndex % grid->GetWidth() != 0 && grid->GetType(myIndex + 1) == Grid::CellType::Wall)
	{
		cell = grid->IndexToWorld(myIndex + 1);
		dist = m_position.x + m_radius - cell.x;
		if (dist > 0)
			m_position.x -= dist;
	}

	if (myIndex - grid->GetWidth() >= 0 && grid->GetType(myIndex - grid->GetWidth()) == Grid::CellType::Wall)
	{
		cell = grid->IndexToWorld(myIndex - grid->GetWidth());
		dist = m_position.y - m_radius - cell.y - cellSize;
		if (dist < 0)
			m_position.y -= dist;
	}

	if ((myIndex / grid->GetWidth()) % grid->GetHeight() != 0 && grid->GetType(myIndex + grid->GetWidth()) == Grid::CellType::Wall)
	{
		cell = grid->IndexToWorld(myIndex + grid->GetWidth());
		dist = m_position.y + m_radius - cell.y;
		if (dist > 0)
			m_position.y -= dist;
	}
}


void MovAble::OnKeyPressed(const sf::Keyboard::Key& keycode)
{
	if (keycode == sf::Keyboard::A)
		m_direction = { -1, 0 };

	else if (keycode == sf::Keyboard::W)
		m_direction = { 0, -1 };

	else if (keycode == sf::Keyboard::D)
		m_direction = { 1, 0 };

	else if (keycode == sf::Keyboard::S)
		m_direction = { 0, 1 };
}


void MovAble::OnKeyReleased(const sf::Keyboard::Key& keycode)
{
	if (keycode == sf::Keyboard::A || keycode == sf::Keyboard::W || 
		keycode == sf::Keyboard::D || keycode == sf::Keyboard::S)
		m_direction = { 0, 0 };
}
