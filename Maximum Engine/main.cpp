#include "Engine.h"
#include <thread>

class PlayerController : public MaximumEngine::Script
{
protected:
	void update()
	{
		if(ME_GetKey(ME_KEYCODE_D)) getGeometry()->position.x += 100 * ME_DELTA_TIME;
		if(ME_GetKey(ME_KEYCODE_A)) getGeometry()->position.x -= 100 * ME_DELTA_TIME;
		if(ME_GetKey(ME_KEYCODE_W)) getGeometry()->setRotation(getGeometry()->getRotation() + 1 * ME_DELTA_TIME);
		if(ME_GetKey(ME_KEYCODE_S)) getGeometry()->setRotation(getGeometry()->getRotation() - 1 * ME_DELTA_TIME);
	}
	void onCollision(MaximumEngine::Collider* collider) 
	{
		getGeometry()->position.x -= 50;
	}
};

int main(int argc, char* args[])
{
	//Init Engine
	ME_Init();

	//Geometry
	ME_Geometry geometry = ME_Geometry();
	geometry.position = ME_Vector2(200, 400);
	geometry.colour = { 255, 255, 255, 255 };
	geometry.setVertices({ ME_Vector2(60, -140), ME_Vector2(20, -30),   ME_Vector2(80, 70),    ME_Vector2(130, 150),  ME_Vector2(70, 160),   ME_Vector2(20, 70),
						   ME_Vector2(-30, 80),  ME_Vector2(-40, 110),  ME_Vector2(-56, 70),   ME_Vector2(-100, 100), ME_Vector2(-70, -110), ME_Vector2(-50, -120) });

	//Create GameObject
	ME_GameObject object = ME_GameObject();
	object.geometry = geometry;
	PlayerController* controller = object.addComponent<PlayerController>();
	MaximumEngine::PolygonCollider* col = object.addComponent<MaximumEngine::PolygonCollider>();
	col->renderOutline = true;

	ME_GameObject object2 = ME_GameObject();
	object2.geometry = ME_Geometry({ ME_Geometry_Rectangle(200, 200) }, ME_Vector2(800, 300));
	object2.geometry.colour = { 255, 255, 255, 255 };
	object2.addComponent<MaximumEngine::Collider>()->renderOutline = true;

	//Start Game
	ME_Start_With_Resolution(1000, 800);

	return 0;
}

