#pragma once

#include "Light.h"
#include "Grid.h"


class Scene3D
{
public:
	Scene3D(float fieldOfView, float unitWidth, float maxRayLength);

	void Draw(sf::RenderWindow* window, const Ray& ray, const Vector2& sightDir);

private:
	float m_FieldOfView;
	float m_unitWidth;
	float m_maxRayLength;
};


class SceneMap
{
public:
	SceneMap(Grid* map, const Light& light, const sf::Color& lineColor = sf::Color::Red);

	void CastRay(Ray& ray);
	void Draw(sf::RenderWindow* window, const Ray& ray);

private:
	sf::Vertex m_toDrawLine[2];

	Grid* m_map;
	Light m_light;
};
