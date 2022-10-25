#include "CInput.h"
#include<Windows.h>

bool Input::gKeyState[256] = { false };
bool Input::OldKeyState[256] = { false };

void Input::Input_SetKeyDown(int key)
{
	gKeyState[key] = true;

}


bool Input::Input_GetKeyDownTrigger(int key)
{
	//連続で
	if (OldKeyState[key] == false && gKeyState[key] == true) {
		OldKeyState[key] = true;
		return gKeyState[key];		
	}
	return 0;
}

bool Input::Input_GetKeyDownPress(int key)
{
	return gKeyState[key];
}


void Input::Input_SetKeyUp(int key)
{
	gKeyState[key] = false;
	OldKeyState[key] = false;
}




