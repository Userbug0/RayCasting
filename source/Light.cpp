#include "Light.h"


Light::Light(float maxRayLength)
	: m_maxRayLength(maxRayLength)
{

}


void Light::CastRay(Grid* grid, Ray& ray)
{
	size_t myIndex = grid->WorldToIndex(ray.position);

	float slope = ray.direction.y / ray.direction.x;
	Vector2 unitStepSize = Vector2(sqrtf(1 + slope * slope), sqrtf(1 + 1 / (slope * slope)));

	Vector2 step;
	Vector2 rayLength1D;

	if (ray.direction.x > 0)
	{
		step.x = 1.f;
		rayLength1D.x = (grid->IndexToWorld(myIndex + 1).x - ray.position.x) * unitStepSize.x;
	}
	else if (ray.direction.x < 0)
	{
		step.x = -1.f;
		rayLength1D.x = (ray.position.x - grid->IndexToWorld(myIndex).x) * unitStepSize.x;
	}

	if (ray.direction.y > 0)
	{
		step.y = (float)grid->GetWidth();
		rayLength1D.y = (grid->IndexToWorld(myIndex + grid->GetWidth()).y - ray.position.y) * unitStepSize.y;
	}
	else if (ray.direction.y < 0)
	{
		step.y = (float)grid->GetWidth();
		step.y = -step.y;
		rayLength1D.y = (ray.position.y - grid->IndexToWorld(myIndex).y) * unitStepSize.y;
	}

	unitStepSize = (float)grid->GetCellSize() * unitStepSize;

	ray.length = getRayLength(grid, rayLength1D, unitStepSize, myIndex, step);
}


float Light::getRayLength(Grid* grid, const Vector2& startLength, const Vector2& unitStep,
	size_t startCell, const Vector2& cellStep)
{
	Vector2 rayLength1D = startLength;
	size_t checkCell = startCell;
	float length = 0.f;
	while (length <= m_maxRayLength)
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
			if (grid->GetType(checkCell) == Grid::CellType::Wall && length <= m_maxRayLength)
				break;
		}
	}

	if (length > m_maxRayLength)
		length = m_maxRayLength;

	return length;
}

