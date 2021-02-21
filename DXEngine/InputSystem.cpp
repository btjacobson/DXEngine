#include "InputSystem.h"

InputSystem::InputSystem()
{

}

InputSystem::~InputSystem()
{

}

InputSystem* InputSystem::GetInstance()
{
	static InputSystem system;
	
	return &system;
}
