#include "LightSource.h"
#include "Settings.h"


LightSource::LightSource(float speed, float fieldOfView, float density, float maxLength)
	: MovAble(speed), m_FieldOfView(fieldOfView), m_density(density), m_maxLength(maxLength), 
	  m_sightDir({1, 0}), m_highlightColor(sf::Color::Green)
{
	m_sightDir.normalize();
}


void LightSource::Draw(sf::RenderWindow* window, Grid* grid)
{
	unHightlight(grid);

	Vector2 myPos = GetPosition();
	Vector2 ray;

	sf::Vertex line[] = { sf::Vertex({0, 0}, sf::Color::Red), sf::Vertex({0, 0}, sf::Color::Red) };
	Vector2 sight = m_sightDir;

	for (float angle = -m_FieldOfView / 2; angle <= m_FieldOfView / 2; angle += 1 / m_density)
	{
		sight.rotate(angle);

		ray = castRay(grid, sight);
		highlight(grid, ray + 5 * sight);

		sight = m_sightDir;

		line[0].position = { myPos.x, myPos.y };
		line[1].position = { ray.x, ray.y };

		window->draw(line, 2, sf::Lines);
	}

	MovAble::Draw(window);
}


Vector2 LightSource::castRay(Grid* grid, const Vector2& sight)
{
	Vector2 myPos = GetPosition();
	size_t myIndex = grid->WorldToIndex(myPos);

	float slope = sight.y / sight.x;
	Vector2 unitStepSize = Vector2( sqrtf(1 + slope * slope), sqrtf(1 + 1 / (slope * slope)) );

	Vector2 step;
	Vector2 rayLength1D;

	if (sight.x > 0)
	{
		step.x = 1.f;
		rayLength1D.x = (grid->IndexToWorld(myIndex + 1).x - myPos.x) * unitStepSize.x;
	}
	else if(sight.x < 0)
	{
		step.x = -1.f;
		rayLength1D.x = (myPos.x - grid->IndexToWorld(myIndex).x) * unitStepSize.x;
	}

	if (sight.y > 0)
	{
		step.y = (float)grid->GetWidth();
		rayLength1D.y = (grid->IndexToWorld(myIndex + grid->GetWidth()).y - myPos.y) * unitStepSize.y;
	}
	else if (sight.y < 0)
	{
		step.y = (float)grid->GetWidth();
		step.y = -step.y;
		rayLength1D.y = (myPos.y - grid->IndexToWorld(myIndex).y) * unitStepSize.y;
	}

	unitStepSize = (float)grid->GetCellSize() * unitStepSize;

	return myPos + sight * getRayLength(grid, rayLength1D, unitStepSize, myIndex, step);
}


float LightSource::getRayLength(Grid* grid, const Vector2& startLength, const Vector2& unitStep,
							      size_t startCell, const Vector2& cellStep)
{
	Vector2 rayLength1D = startLength;
	size_t checkCell = startCell;
	float length = 0.f;
	while (length <= m_maxLength)
	{
		if (rayLength1D.x < rayLength1D.y)
		{
			checkCell += (int)cellStep.x;
			length = rayLength1D.x;
			rayLength1D.x += unitStep.x;
		}
		else
		{
			checkCell += (int)cellStep.y;
			length = rayLength1D.y;
			rayLength1D.y += unitStep.y;
		}
		if (checkCell >= 0 && checkCell < grid->GetSize())
		{
			if (grid->GetType(checkCell) == Grid::CellType::Wall && length <= m_maxLength)
				break;
		}
	}

	if (length > m_maxLength)
		length = m_maxLength;

	return length;
}


void LightSource::highlight(Grid* grid, const Vector2& ray)
{
	size_t cell = grid->WorldToIndex(ray);
	if (grid->GetType(cell) == Grid::CellType::Wall)
		grid->SetCellColor(cell, sf::Color::Green);
}


void LightSource::unHightlight(Grid* grid)
{
	for (size_t i = 0; i < grid->GetSize(); ++i)
	{
		if (grid->GetCell(i).color == m_highlightColor)
			grid->SetCellColor(i, Grid::DefaultColor);
	}
}


void LightSource::LookAt(const Vector2& point)
{
	m_sightDir = point - GetPosition();
	m_sightDir.normalize();
}
