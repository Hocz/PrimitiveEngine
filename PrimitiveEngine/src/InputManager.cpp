#include "InputManager.h"
#include "SDL.h"
#include "glm.hpp"

void InputManager::HandleEvents(SDL_Event& event)
{

	switch (event.type)
	{
        case SDL_KEYDOWN:
        {
            if (event.key.repeat)
                break;

            InputState& state = keyStates[event.key.keysym.scancode];
            state.SetInput(true);
            break;
        }

        case SDL_KEYUP:
        {
            InputState& state = keyStates[event.key.keysym.scancode];
            state.SetInput(false);
            break;
        }

        case SDL_MOUSEBUTTONDOWN:
        {
            InputState& state = mouseStates[event.button.button];
            state.SetInput(true);
            break;
        }

        case SDL_MOUSEBUTTONUP:
        {
            InputState& state = mouseStates[event.button.button];
            state.SetInput(false);
            break;
        }


        case SDL_MOUSEMOTION:
        {
            mouseX = event.motion.x;
            mouseY = event.motion.y;
            break;
        }

	}
}

// key inputs
bool InputManager::KeyDown(Key key)
{
	InputState& state = keyStates[(int)key];
	return state.down;
}

bool InputManager::KeyPressed(Key key)
{
	InputState& state = keyStates[(int)key];
	return state.down && state.updateFrame == GetFrameCount();
}

bool InputManager::KeyUp(Key key)
{
	InputState& state = keyStates[(int)key];
	return !state.down && state.updateFrame == GetFrameCount();
}

// mount inputs
bool InputManager::MouseButtonDown(MouseButton button)
{
	InputState& state = mouseStates[(int)button];
	return state.down;
}

bool InputManager::MouseButtonPressed(MouseButton button)
{
	InputState& state = mouseStates[(int)button];
	return state.down && state.updateFrame == GetFrameCount();
}

bool InputManager::MouseButtonUp(MouseButton button)
{
	InputState& state = mouseStates[(int)button];
	return !state.down && state.updateFrame == GetFrameCount();
}

// mouse movement
int InputManager::MouseX() const
{
	return mouseX;
}

int InputManager::MouseY() const
{
	return mouseY;
}


