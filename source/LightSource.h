#pragma once

#include "MovAble.h"
#include "Light.h"
#include "Scenes.h"


class LightSource: public MovAble
{
public:
	LightSource(float speed, Grid* map, const Light& light, float fiedldOfView, float density);
  
	void Draw(sf::RenderWindow* window);
	void LookAt(const Vector2& point);

private:
	Scene3D m_scene3D;
	SceneMap m_sceneMap;
	Vector2 m_sightDir;
	float m_density;
	float m_FieldOfView;
};

