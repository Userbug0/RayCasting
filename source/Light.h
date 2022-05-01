#pragma once

#include "Vector2.h"
#include "Grid.h"


struct Ray
{
	Vector2 GetEndPoint() const { return position + direction * length; }

	Vector2 position;
	Vector2 direction;
	float length;
};


class Light
{
public:
	Light(float maxRayLength);

	/// <param name="ray">: will be changed only length</param>
	void CastRay(Grid* grid, Ray& ray);
	float GetMaxRayLength() const { return m_maxRayLength; }

private:
	float getRayLength(Grid* grid, const Vector2& startLength, const Vector2& unitStep,
		size_t startCell, const Vector2& cellStep);

	float m_maxRayLength;
};
