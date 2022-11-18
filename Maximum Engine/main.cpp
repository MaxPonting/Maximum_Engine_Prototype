#include "Engine.h"

class PlayerController : public MaximumEngine::Script
{
protected:
	void update()
	{
		if(ME_GetKey(ME_KEYCODE_D)) setGPosition(ME_Vector2(G_POS.x + 100 * ME_DELTA_TIME, G_POS.y));
		if(ME_GetKey(ME_KEYCODE_A)) setGPosition(ME_Vector2(G_POS.x - 100 * ME_DELTA_TIME, G_POS.y));
		if(ME_GetKey(ME_KEYCODE_W)) setGPosition(ME_Vector2(G_POS.x, G_POS.y - 100 * ME_DELTA_TIME));
	    if(ME_GetKey(ME_KEYCODE_S)) setGPosition(ME_Vector2(G_POS.x , G_POS.y + 100 * ME_DELTA_TIME));
		if(ME_GetKey(ME_KEYCODE_RIGHT)) setGRotation(G_ROT + 100 * ME_DELTA_TIME);
		if(ME_GetKey(ME_KEYCODE_LEFT))  setGRotation(G_ROT - 100 * ME_DELTA_TIME);
	}
	void onCollision(const MaximumEngine::Collider* collider) 
	{
		setGPosition(ME_Vector2(G_POS.x - 200 * ME_DELTA_TIME, G_POS.y));
	}
};

class Rotator : public MaximumEngine::Script
{
protected:
	void update()
	{
		setGRotation(G_ROT + 0.5 * ME_DELTA_TIME);
	}
};

int main(int argc, char* args[])
{
	//Init Engine
	ME_Init_Threading();
	//ME_Init();

	//Create Objects		
	ME_Geometry geometry = ME_Geometry({ ME_Geometry_Rectangle(200, 200) }, ME_Vector2(200, 400));
	geometry.setColour({ 255, 0, 255, 255 });
	//geometry.setRotation(45);
	ME_GameObject* object = new ME_GameObject();
	object->setGeometry(geometry);
	object->addComponent<PlayerController>();
	MaximumEngine::RectangleCollider* col = object->addComponent<MaximumEngine::RectangleCollider>();

	ME_Geometry geometry2 = ME_Geometry({ ME_Geometry_Rectangle(100, 100) }, ME_Vector2(500, 400));
	geometry2.setColour({ 255, 0, 255, 255 });
	ME_GameObject* object2 = new ME_GameObject();
	object2->setGeometry(geometry2);
	object2->addComponent<MaximumEngine::RectangleCollider>();
		
	//Start Game
	ME_Start_With_Resolution(1600, 800);

	return 0;
}

