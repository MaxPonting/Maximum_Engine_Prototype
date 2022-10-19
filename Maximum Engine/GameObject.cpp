#include "GameObject.h"
#include "Engine.h"
#include "Time.h"

//CONSTRUCTORS
MaximumEngine::GameObject::GameObject() :geometry(Geometry()) 
{
	ME_Engine::gameObjects.push_back(this);
}

//METHODS
void MaximumEngine::GameObject::update()
{
	//Update components
	for (int i = 0; i < components.size(); i++)
	{
		components[i]->update();
	}
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



