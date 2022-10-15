#include "Input.h"
#include "Log.h"
#include "SDL.h"

std::bitset<MAX_KEYS> MaximumEngine::Input::keyboard;
std::bitset<MAX_KEYS> MaximumEngine::Input::keyboardDown;
std::bitset<MAX_KEYS> MaximumEngine::Input::keyboardUp;

//METHODS
void MaximumEngine::Input::updateInput()
{
	//Keystates
	const Uint8* keystates = SDL_GetKeyboardState(NULL);

	//Reset up and down keyboards
	keyboardDown.reset();
	keyboardUp.reset();

    //Assign to keyboard
	for (int i = 0; i < MAX_KEYS; i++)
	{
		if (keyboard[i] == false && keystates[i] == true)
		{
			keyboardDown[i] = true;
		}
		else if (keyboard[i] == true && keystates[i] == false)
		{
			keyboardUp[i] = true;
		}
		
		keyboard[i] = keystates[i];
	}
}
bool MaximumEngine::Input::getKey(int i)
{
	return keyboard[i];
}
bool MaximumEngine::Input::getKeyDown(int i)
{
	return keyboardDown[i];
}
bool MaximumEngine::Input::getKeyUp(int i)
{
	return keyboardUp[i];
}

