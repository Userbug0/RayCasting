#pragma once

#include "MovAble.h"


class LightSource: public MovAble
{
public:
	LightSource(float speed, float fieldOfView, float density, float maxLength);
  
	void Draw(sf::RenderWindow* window, Grid* grid);
	void LookAt(const Vector2& point);

private:
	/// <param name="sight">: Must be normalized</param>
	Vector2 castRay(Grid* grid, const Vector2& sight);
	float getRayLength(Grid* grid, const Vector2& startLength, const Vector2& unitStep,
				         size_t startCell, const Vector2& cellStep);

	void highlight(Grid* grid, const Vector2& ray);
	void unHightlight(Grid* grid);

	sf::Color m_highlightColor;

	Vector2 m_sightDir;
	float m_density;
	float m_FieldOfView;
	float m_maxLength;
};

