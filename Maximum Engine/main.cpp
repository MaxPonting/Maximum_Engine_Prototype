#include "Engine.h"

class PlayerController : public MaximumEngine::Script
{
protected:
	void update()
	{
		if(ME_GetKey(ME_KEYCODE_D)) setGPosition(ME_Vector2(G_POS.x + 100 * ME_DELTA_TIME, G_POS.y));
		if(ME_GetKey(ME_KEYCODE_A)) setGPosition(ME_Vector2(G_POS.x - 100 * ME_DELTA_TIME, G_POS.y));
		if(ME_GetKey(ME_KEYCODE_W)) setGRotation(G_ROT + 1 * ME_DELTA_TIME);
		if(ME_GetKey(ME_KEYCODE_S)) setGRotation(G_ROT - 1 * ME_DELTA_TIME);
	}
	void onCollision(MaximumEngine::Collider* collider) 
	{
		setGPosition(ME_Vector2(G_POS.x - 25, G_POS.y));
	}
};

class Rotator : public MaximumEngine::Script
{
protected:
	void update()
	{
		setGRotation(G_ROT + 1 * ME_DELTA_TIME);
	}
};

int main(int argc, char* args[])
{
	//Init Engine
	//ME_Init_Threading();
	ME_Init();

	//Create Objects	
	
	for (int posX = 100; posX < 1600; posX += 150)
	{
		for (int posY = 100; posY < 800; posY += 150)
		{
			ME_Geometry geometry = ME_Geometry({ ME_Geometry_Rectangle(100, 100) }, ME_Vector2(posX, posY));
			geometry.setColour({ 255, 0, 255, 255 });
			ME_GameObject* object = new ME_GameObject();
			object->setGeometry(geometry);
			object->addComponent<Rotator>();
		}		
	}
	

	/*
	ME_Geometry geometry = ME_Geometry({ ME_Geometry_Rectangle(100, 100) }, ME_Vector2(500, 400));
	geometry.setColour({ 255, 0, 255, 255 });
	ME_GameObject* object = new ME_GameObject();
	object->setGeometry(geometry);
	object->addComponent<Rotator>();
	*/
		
	//Start Game
	ME_Start_With_Resolution(1600, 800);

	return 0;
}

