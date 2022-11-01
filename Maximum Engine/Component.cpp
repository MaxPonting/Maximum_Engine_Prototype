#include "Engine.h"
#include "Component.h"

//COMPONENT
//Methods
void MaximumEngine::Component::init(GameObject* obj, Geometry* geo) 
{
	gameObject = obj;
	geometry = geo;
	start();
}
//Getters
const MaximumEngine::GameObject& MaximumEngine::Component::getGameObject()
{
	return *gameObject;
}
const MaximumEngine::Geometry& MaximumEngine::Component::getGeometry()
{
	return *geometry;
}
//Geometry access
void MaximumEngine::Component::setGPosition(const Vector2 pos)
{
	geometry->setPosition(pos);
}
void MaximumEngine::Component::setGRotation(const float z)
{
	geometry->setRotation(z);
}

//SCRIPT


