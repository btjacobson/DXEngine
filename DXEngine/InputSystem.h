#pragma once


class InputSystem
{
public:
	InputSystem();
	~InputSystem();

	void AddListener();

	static InputSystem* GetInstance();

private:

};
