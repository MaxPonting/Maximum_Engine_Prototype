#include "Collider.h"
#include "Geometry.h"
#include "Algorithm.h"

//COLLIDER
//Methods
void MaximumEngine::Collider::update(std::vector<Component*> comps, std::vector<Collider*> cols)
{
	//Check which colliders are close
	std::vector<Collider*> closeColliders = getCloseColliders(cols);
	bool collision = false;
	//Check line intersection with colliders
	std::vector<Vector2> vertices1 = getVertices();
	std::vector<Vector2> vertices2;
	for (int i = 0; i < closeColliders.size(); i++)
	{
		//Check if a collison occurs with each collider
		if (Algorithm::isCollisionPolygon(vertices1, closeColliders[i]->G_VERT, G_POS, closeColliders[i]->G_POS))
		{
			alertComponents(closeColliders[i], comps);
		}
	}
}
void MaximumEngine::Collider::render(SDL_Renderer* renderer)
{
	//Return if renderOutline is false
	if (!renderOutline) { return; }
	//Render Outline Of Collider in Green
	SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
	std::vector<Vector2> vertices = getVertices();
	int j = vertices.size() - 1;
	for (int i = 0; i < vertices.size(); i++)
	{
		//Render lines
		SDL_RenderDrawLine(renderer, vertices[j].x + G_POS.x, vertices[j].y + G_POS.y, vertices[i].x + G_POS.x, vertices[i].y + G_POS.y);
		j = i;
	}
}
void MaximumEngine::Collider::alertComponents(Collider* collider, std::vector<Component*> comps)
{
	for (int i = 0; i < comps.size(); i++)
	{
		comps[i]->onCollision(collider);
	}
}
std::vector<MaximumEngine::Collider*> MaximumEngine::Collider::getCloseColliders(std::vector<Collider*> cols)
{
	std::vector<Collider*> closeColliders;
	for (int i = 0; i < cols.size(); i++)
	{
		float distance = (G_POS - cols[i]->G_POS).getMagnitude();
		if ((distance < getLargestVertice() + cols[i]->getLargestVertice()) && this != cols[i])
		{
			closeColliders.push_back(cols[i]);
		}
	}
	return closeColliders;
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
	int val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);

	if (val == 0) return 0;

	return (val > 0) ? 1 : 2;
}
bool MaximumEngine::Collider::onLineSegment(Vector2 p, Vector2 q, Vector2 r)
{
	if (q.x <= std::max(p.x, r.x) && q.x >= std::min(p.x, r.x) &&
		q.y <= std::max(p.y, r.y) && q.y >= std::min(p.y, r.y)) return true;

	return false;
}
//Getters
std::vector<ME_Vector2> MaximumEngine::Collider::getVertices()
{
	return getGeometry().getVertices();
}
float MaximumEngine::Collider::getLargestVertice()
{
	return getGeometry().getLargestVertice();
}

//POLYGON COLLIDER
//Methods
void MaximumEngine::PolygonCollider::start()
{
	//Set default vertices to match geometry
	vertices = getGeometry().getVertices();
}
void MaximumEngine::PolygonCollider::rotate(float z)
{
	rotatedVertices.clear();
	//Rotate each vertice
	for (int i = 0; i < vertices.size(); i++)
	{
		Vector2 rotatedVector;
		rotatedVector.x = vertices[i].x * cos(rotation) - sin(rotation) * vertices[i].y;
		rotatedVector.y = vertices[i].x * sin(rotation) + cos(rotation) * vertices[i].y;
		rotatedVertices.push_back(rotatedVector);
	}
}
//Getters
std::vector<ME_Vector2> MaximumEngine::PolygonCollider::getVertices()
{
	return vertices;
}
float MaximumEngine::PolygonCollider::getLargestVertice()
{
	float largest = 0;
	for (int i = 0; i < vertices.size(); i++)
	{
		float current = vertices[i].getMagnitude();
		if (current > largest)
		{
			largest = current;
		}
	}
	return largest;
}
//Setters
void MaximumEngine::PolygonCollider::setVertices(std::vector<Vector2> v)
{
	vertices = v;
}

//CIRCLE COLLIDER
//Methods
void MaximumEngine::CircleCollider::update(std::vector<Component*> comps, std::vector<Collider*> cols)
{
	//Check which colliders are close
	std::vector<Collider*> closeColliders = getCloseColliders(cols);
	//Check type of colliders
	for (int i = 0; i < closeColliders.size(); i++)
	{
		//Call collision if collider is circle
		if (dynamic_cast<CircleCollider*>(closeColliders[i]))
		{
			alertComponents(closeColliders[i], comps);
		}
		//Circle and Polygon Collision
		else
		{

		}
	}
}
float MaximumEngine::CircleCollider::getLargestVertice()
{
	return radius;
}
