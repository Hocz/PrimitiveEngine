#pragma once

#include "Input.h"
#include "Game.h"

class InputManager
{
public:

	void HandleEvents(SDL_Event& event);

	bool KeyDown(Key key);
	bool KeyPressed(Key key);
	bool KeyUp(Key key);

	bool MouseButtonDown(MouseButton button);
	bool MouseButtonPressed(MouseButton button);
	bool MouseButtonUp(MouseButton button);

	int MouseX() const;
	int MouseY() const;

private:

	struct InputState
	{
		bool down = false;
		unsigned int updateFrame = 0;

		void SetInput(bool newDown)
		{
			down = newDown;
			updateFrame = GetFrameCount();
		}
	};

	InputState keyStates[(int)Key::Count];
	InputState mouseStates[(int)MouseButton::Count];
	int mouseX;
	int mouseY;
};