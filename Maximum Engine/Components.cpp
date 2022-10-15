#include "Engine.h"

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


//COLLIDER
//Methods
void MaximumEngine::Collider::update()
{
	//Check which colliders are close
	std::vector<Collider*> closeColliders;
	for (int i = 0; i < ME_ENGINE_COLLIDERS.size(); i++)
	{
		float distance = (getGeometry()->position - ME_ENGINE_COLLIDERS[i]->getGeometry()->position).getMagnitude();
		if((distance < getGeometry()->getLargestVertice() + ME_ENGINE_COLLIDERS[i]->getGeometry()->getLargestVertice()) && this != ME_ENGINE_COLLIDERS[i])
		{
			closeColliders.push_back(ME_ENGINE_COLLIDERS[i]);
		}
	}
	bool collision = false;
	//Check line intersection with colliders
	std::vector<Vector2> vertices1 = getGeometry()->rotatedVertices;
	std::vector<Vector2> vertices2;
	for (int i = 0; i < closeColliders.size(); i++)
	{
		vertices2 = closeColliders[i]->getGeometry()->rotatedVertices;
		int j1 = vertices1.size() - 1;
		for (int c1 = 0; c1 < vertices1.size(); c1++)
		{
			int j2 = vertices2.size() - 1;
			for (int c2 = 0; c2 < vertices2.size(); c2++)
			{
				Vector2 point1 = getGeometry()->position + vertices1[j1];
				Vector2 point2 = getGeometry()->position + vertices1[c1];
				Vector2 point3 = closeColliders[i]->getGeometry()->position + vertices2[j2];
				Vector2 point4 = closeColliders[i]->getGeometry()->position + vertices2[c2];
				if (doIntersect(point1, point2, point3, point4))
				{
					getGeometry()->colour = { 255, 0, 0, 255 };
					collision = true;
					alertScripts(closeColliders[i]);
					break;
				}
				j2 = c2;
			}
			j1 = c1;
			if (collision) { break; }
		}
	}
	if(!collision) { getGeometry()->colour = { 0, 255, 0, 255 }; }
}
void MaximumEngine::Collider::alertScripts(Collider* collider)
{
	std::vector<Component*> components = getGameObject()->components;
	for (int i = 0; i < components.size(); i++)
	{
		if (dynamic_cast<Script*>(components[i]) != nullptr)
		{
			Script* script = (Script*)(components[i]);
			script->onCollision(collider);
		}
	}
}
bool MaximumEngine::Collider::doIntersect(Vector2 p1, Vector2 q1, Vector2 p2, Vector2 q2)
{
	int o1 = lineOrientation(p1, q1, p2);
	int o2 = lineOrientation(p1, q1, q2);
	int o3 = lineOrientation(p2, q2, p1);
	int o4 = lineOrientation(p2, q2, q1);

	//General Case
	if (o1 != o2 && o3 != o4) return true;

	//Special Cases
	if (o1 == 0 && onLineSegment(p1, p2, q1)) return true;
	if (o2 == 0 && onLineSegment(p1, q2, q1)) return true;
	if (o3 == 0 && onLineSegment(p2, p1, q2)) return true;
	if (o4 == 0 && onLineSegment(p2, q1, q2)) return true;

	return false;
}
int MaximumEngine::Collider::lineOrientation(Vector2 p, Vector2 q, Vector2 r)
{
	int val = (q.y - p.y) * (r.x - q.x) -
		(q.x - p.x) * (r.y - q.y);

	if (val == 0) return 0;

	return (val > 0) ? 1 : 2;
}
bool MaximumEngine::Collider::onLineSegment(Vector2 p, Vector2 q, Vector2 r)
{
	if (q.x <= std::max(p.x, r.x) && q.x >= std::min(p.x, r.x) &&
		q.y <= std::max(p.y, r.y) && q.y >= std::min(p.y, r.y)) return true;

	return false;
}