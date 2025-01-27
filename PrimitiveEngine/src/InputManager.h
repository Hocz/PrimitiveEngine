#pragma once

#include "Input.h"
#include "Game.h"

class InputManager
{
public:

	InputManager(const InputManager&) = delete;
	InputManager& operator=(const InputManager&) = delete;

	static InputManager& Instance()
	{
		static InputManager instance;
		return instance;
	}

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

	InputManager() { }

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
	int mouseX = 0;
	int mouseY = 0;
};