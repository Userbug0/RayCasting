#include "LightSource.h"
#include "Settings.h"


LightSource::LightSource(float speed, Grid* map, const Light& light, float fieldOfView, float density)
	: MovAble(speed, map->GetPosition() + Vector2(MAP_WIDTH / 2, MAP_HEIGHT / 2)),
	  m_sceneMap(map, light), m_scene3D(fieldOfView, density / 10, light.GetMaxRayLength()), 
	  m_FieldOfView(fieldOfView), m_density(density), m_sightDir({1, 0})
{
	m_sightDir.normalize();
}


void LightSource::Draw(sf::RenderWindow* window)
{
	Ray ray;
	ray.position = GetPosition();

	Vector2 sight = m_sightDir;
	for (float angle = -m_FieldOfView / 2; angle <= m_FieldOfView / 2; angle += 1 / m_density)
	{
		sight.rotate(angle);
		ray.direction = sight;

		m_sceneMap.CastRay(ray);

		m_scene3D.Draw(window, ray, m_sightDir);
		m_sceneMap.Draw(window, ray);

		sight = m_sightDir;
	}

	MovAble::Draw(window);
}


void LightSource::LookAt(const Vector2& point)
{
	m_sightDir = point - GetPosition();
	m_sightDir.normalize();
}
