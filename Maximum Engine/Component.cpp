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
MaximumEngine::GameObject* MaximumEngine::Component::getGameObject()
{
	return gameObject;
}
MaximumEngine::Geometry* MaximumEngine::Component::getGeometry()
{
	return geometry;
}

//SCRIPT


