#include "Collider.h"
#include "Geometry.h"

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
		vertices2 = closeColliders[i]->getVertices();
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
					collision = true;
					alertComponents(closeColliders[i], comps);
					break;
				}
				j2 = c2;
			}
			j1 = c1;
			if (collision) { break; }
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
	Vector2 position = getGeometry()->position;
	int j = vertices.size() - 1;
	for (int i = 0; i < vertices.size(); i++)
	{
		//Render lines
		SDL_RenderDrawLine(renderer, vertices[j].x + position.x, vertices[j].y + position.y, vertices[i].x + position.x, vertices[i].y + position.y);
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
		float distance = (getGeometry()->position - cols[i]->getGeometry()->position).getMagnitude();
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
	return getGeometry()->rotatedVertices;
}
float MaximumEngine::Collider::getLargestVertice()
{
	return getGeometry()->getLargestVertice();
}

//POLYGON COLLIDER
//Methods
void MaximumEngine::PolygonCollider::start()
{
	//Set default vertices to match geometry
	vertices = getGeometry()->rotatedVertices;
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
