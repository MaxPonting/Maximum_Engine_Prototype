#include "GameObject.h"
#include "Engine.h"
#include "Time.h"

//CONSTRUCTORS
MaximumEngine::GameObject::GameObject() :geometry(Geometry()) 
{
	Engine::gameObjects.push_back(this);
}

//METHODS
void MaximumEngine::GameObject::update(std::vector<Collider*> cols)
{
	//Update components
	for (int i = 0; i < components.size(); i++)
	{
		if (dynamic_cast<Collider*>(components[i]))
		{
			components[i]->update(components, cols);
		}
		components[i]->update();
	}
}
void MaximumEngine::GameObject::updateGeometry()
{
	//Update geometry
	geometry.update();
}
void MaximumEngine::GameObject::render(SDL_Renderer* renderer)
{
	//Render geometry
	geometry.render(renderer);

	//Render components
	for (int i = 0; i < components.size(); i++)
	{
		components[i]->render(renderer);
	}
}

//SETTERS
void MaximumEngine::GameObject::setGeometry(const Geometry g)
{
	geometry = g;
}

//GETTERS
const ME_Geometry& MaximumEngine::GameObject::getGeometry()
{
	return geometry;
}



