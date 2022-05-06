#include "Scenes.h"
#include "Settings.h"


Scene3D::Scene3D(float fieldOfView, float unitWidth, float maxRayLength)
	: m_FieldOfView(fieldOfView), m_unitWidth(unitWidth), m_maxRayLength(maxRayLength)
{

}


void Scene3D::Draw(sf::RenderWindow* window, const Ray& ray, const Vector2& sightDir)
{
	Vector2 sight = sightDir;
	float minX = Vector2::DotProduct(sightDir, sight.rotate(m_FieldOfView));
	float x = Vector2::DotProduct(sight.rotate(-m_FieldOfView / 2), ray.direction);

	float worldX = MAP_WIDTH + GAME_WIDTH * (x - minX) / (1 - minX);

	sf::RectangleShape rect({ m_unitWidth, GAME_HEIGHT - (ray.length / m_maxRayLength * GAME_HEIGHT) });
	rect.setPosition({ worldX, (GAME_HEIGHT - rect.getSize().y) / 2 });

	uint8_t color = 255 - (int)(ray.length / m_maxRayLength * 255);
	rect.setFillColor({ color, color, color });

	window->draw(rect);
}


SceneMap::SceneMap(Grid* map, const Light& light, const sf::Color& lineColor)
	: m_map(map), m_light(light)
{
	m_toDrawLine[0].color = lineColor;
	m_toDrawLine[1].color = lineColor;
}


void SceneMap::CastRay(Ray& ray)
{
	m_light.CastRay(m_map, ray);
}


void SceneMap::Draw(sf::RenderWindow* window, const Ray& ray)
{
	m_toDrawLine[0].position = ray.position;
	m_toDrawLine[1].position = ray.GetEndPoint();

	window->draw(m_toDrawLine, 2, sf::Lines);
}
