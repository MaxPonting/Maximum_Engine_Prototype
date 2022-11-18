#include "Collider.h"
#include "Geometry.h"
#include "Algorithm.h"
#include <typeinfo>

//COLLIDER
//Methods
void MaximumEngine::Collider::update(std::vector<Component*> comps, std::vector<Collider*> cols)
{
	//Check which colliders are close
	std::vector<Collider*> closeColliders = getCloseColliders(cols);
	//Check type of colliders
	for (int i = 0; i < closeColliders.size(); i++)
	{
		//Check Collison
		if (dynamic_cast<MaximumEngine::PolygonCollider*>(closeColliders[i]))
		{
			if (isCollision(*dynamic_cast<MaximumEngine::PolygonCollider*>(closeColliders[i]))) alertComponents(closeColliders[i], comps);
		}
		else if (dynamic_cast<MaximumEngine::RectangleCollider*>(closeColliders[i]))
		{
			if (isCollision(*dynamic_cast<MaximumEngine::RectangleCollider*>(closeColliders[i]))) alertComponents(closeColliders[i], comps);
		}
		else if (dynamic_cast<MaximumEngine::CircleCollider*>(closeColliders[i]))
		{
			if (isCollision(*dynamic_cast<MaximumEngine::CircleCollider*>(closeColliders[i]))) alertComponents(closeColliders[i], comps);
		}
		else
		{
			if (isCollision(*closeColliders[i])) alertComponents(closeColliders[i], comps);
		}
	}
}
void MaximumEngine::Collider::render(SDL_Renderer* renderer)
{
	//Return if renderOutline is false
	if (!renderOutline) { return; }
	//Render Outline Of Collider in Green
	SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
	std::vector<Vector2> vertices = getRotatedVertices();
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
//Collison Checking
bool MaximumEngine::Collider::isCollision(Collider collider)
{
	return Algorithm::isCollisionPolygon(getRotatedVertices(), collider.getRotatedVertices(), G_POS, collider.G_POS);
}
bool MaximumEngine::Collider::isCollision(PolygonCollider collider)
{
	return Algorithm::isCollisionPolygon(getRotatedVertices(), collider.getRotatedVertices(), G_POS, collider.G_POS);
}
bool MaximumEngine::Collider::isCollision(RectangleCollider collider)
{
	return Algorithm::isCollisionPolygon(getVertices(), collider.getRotatedVertices(), G_POS, collider.G_POS);
}
bool MaximumEngine::Collider::isCollision(CircleCollider collider)
{
	return Algorithm::isCollisionPolygonCircle(getRotatedVertices(), collider.radius, G_POS, collider.G_POS);
}
//Getters
std::vector<ME_Vector2> MaximumEngine::Collider::getVertices()
{
	return getGeometry().getVertices();
}
std::vector<ME_Vector2> MaximumEngine::Collider::getRotatedVertices()
{
	std::vector<Vector2> rotatedVerts;
	for (int i = 0; i < G_VERT.size(); i++)
	{
		Angle angle = G_ROT + rotation.getDeg();
		rotatedVerts.push_back(G_VERT[i].getRotate((rotation + G_ROT).getDeg()));
	}
	return rotatedVerts;
}
float MaximumEngine::Collider::getLargestVertice()
{
	return getGeometry().getLargestVertice();
}
float MaximumEngine::Collider::getRotation()
{
	return rotation.getDeg();
}
//Setters
void MaximumEngine::Collider::setRotation(float z)
{
	rotation = z;
}


//POLYGON COLLIDER
//Methods
void MaximumEngine::PolygonCollider::start()
{
	//Set default vertices to match geometry
	vertices = getGeometry().getVertices();
}
//Getters
std::vector<ME_Vector2> MaximumEngine::PolygonCollider::getVertices()
{
	return vertices;
}
std::vector<ME_Vector2> MaximumEngine::PolygonCollider::getRotatedVertices()
{
	std::vector<Vector2> rotatedVerts;
	for (int i = 0; i < vertices.size(); i++)
	{
		rotatedVerts.push_back(vertices[i].getRotate((rotation + G_ROT).getDeg()));
	}
	return rotatedVerts;
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


//RECTANGLE COLLIDER
//Methods
void MaximumEngine::RectangleCollider::start()
{
	width = getGeometry().getWidth();
	height = getGeometry().getHeight();
}
//Collison Checking
bool MaximumEngine::RectangleCollider::isCollision(Collider collider)
{
	return Algorithm::isCollisionPolygon(collider.getRotatedVertices(), getRotatedVertices(), collider.G_POS, G_POS);
}
bool MaximumEngine::RectangleCollider::isCollision(PolygonCollider collider)
{
	return Algorithm::isCollisionPolygon(collider.getRotatedVertices(), collider.getRotatedVertices(), collider.G_POS, G_POS);
}
bool MaximumEngine::RectangleCollider::isCollision(RectangleCollider collider)
{
	//AXIS ALIGNED
	if(rotation + G_ROT == collider.getRotation() + collider.G_ROT)
	return Algorithm::isCollisionRectangle(height, width, collider.height, collider.width, G_POS, collider.G_POS);
	
	//NOT ALIGNED
	return Algorithm::isCollisionPolygon(getRotatedVertices(), collider.getRotatedVertices(), G_POS, collider.G_POS);
}
bool MaximumEngine::RectangleCollider::isCollision(CircleCollider collider)
{
	//AXIS ALIGNED
	if ((rotation + G_ROT).getDeg() == 0)
	return Algorithm::isCollisionRectangleCircle(height, width, collider.radius, G_POS, collider.G_POS);

	//NOT ALIGNED
	return Algorithm::isCollisionPolygonCircle(getRotatedVertices(), collider.radius, G_POS, collider.G_POS);
}
//Getters
std::vector<ME_Vector2> MaximumEngine::RectangleCollider::getRotatedVertices()
{	
	float rad = (rotation + G_ROT).getRad();
	return 
	{
		Vector2(width / 2, height / 2).getRotate(rad), Vector2(-width / 2, height / 2).getRotate(rad),
		Vector2(-width / 2, -height / 2).getRotate(rad), Vector2(width / 2, -height / 2).getRotate(rad)
	};
}


//CIRCLE COLLIDER
//Methods
void MaximumEngine::CircleCollider::start()
{
	radius = getGeometry().getLargestVertice();
}
//Collison Checking
bool MaximumEngine::CircleCollider::isCollision(Collider collider)
{
	return Algorithm::isCollisionPolygonCircle(collider.getRotatedVertices(), radius, collider.G_POS, G_POS);
}
bool MaximumEngine::CircleCollider::isCollision(PolygonCollider collider)
{
	return Algorithm::isCollisionPolygonCircle(collider.getRotatedVertices(), radius, collider.G_POS, G_POS);
}
bool MaximumEngine::CircleCollider::isCollision(RectangleCollider collider)
{
	//AXIS ALIGNED
	if (collider.getRotation() + collider.G_ROT == 0)
	return Algorithm::isCollisionRectangleCircle(collider.height, collider.width, radius, collider.G_POS, G_POS);

	//NOT ALIGNED
	return Algorithm::isCollisionPolygonCircle(collider.getRotatedVertices(), radius, collider.G_POS, G_POS);
}
bool MaximumEngine::CircleCollider::isCollision(CircleCollider collider)
{
	return radius + collider.radius <= (G_POS - collider.G_POS).getMagnitude();
}
//Getters
float MaximumEngine::CircleCollider::getLargestVertice()
{
	return radius;
}
