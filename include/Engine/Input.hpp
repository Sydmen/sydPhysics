#ifndef SYDPHYSICS_INPUT_H
#define SYDPHYSICS_INPUT_H

#include <map>
#include <Math/Mathematics.hpp>

using namespace std;
using namespace SydPhysics;

class InputHandler
{
public:
	void PrepareUpdate()
	{
		for(auto const& kvp : m_keyStates)
		{
			if(kvp.second == KeyState::JustDown)
			{
				m_keyStates[kvp.first] = KeyState::Down;
			}
		}
	}

	void Update(const SDL_Event* event)
	{
		PrepareUpdate();

		KeyState newState;
		int keyIndex = event->key.keysym.sym;

		if(event->key.type == SDL_KEYDOWN && m_keyStates[keyIndex] != KeyState::Down)
			newState = KeyState::JustDown;
		else if(event->key.type == SDL_KEYUP)
			newState = KeyState::Up;

		m_keyStates[keyIndex] = newState;
	}

	bool KeyDown(int iKeyIndex)
	{
		if(m_keyStates.count(iKeyIndex) > 0)
		{
			KeyState state = m_keyStates[iKeyIndex];
			if(state == KeyState::Down || state == KeyState::JustDown)
				return true;
			else
				return false;
		}

		return false;
	}

	bool KeyJustDown(int iKeyIndex)
	{
		if(m_keyStates.count(iKeyIndex) > 0)
		{
			KeyState state = m_keyStates[iKeyIndex];
			if(state == KeyState::JustDown)
				return true;
			else
				return false;
		}

		return false;
	}

	bool KeyUp(int iKeyIndex)
	{
		if(m_keyStates.count(iKeyIndex) > 0)
		{
			if(m_keyStates[iKeyIndex] == KeyState::Up)
				return true;
			else
				return false;
		}

		return false;
	}	


	//Probably a better way but idk know it
	//in a perfect world, you can include numbers in the beginning of a method without errors in sublime text
	//:(
	float OneDMap(int iUp, int iDown)
	{
		float res = 0;
		if(KeyDown(iUp)) ++res;
		if(KeyDown(iDown)) --res;
		return res;
	}

	Vector2f TwoDMap(int iUp, int iDown, int iLeft, int iRight)
	{
		Vector2f vec = Vector2f(0,0);

		if(KeyDown(iUp))
			vec = vec + Vector2f(0,-1);

		if(KeyDown(iDown))
			vec = vec + Vector2f(0,1);

		if(KeyDown(iLeft))
			vec = vec + Vector2f(-1,0);

		if(KeyDown(iRight))
			vec = vec + Vector2f(1,0);

		return vec;
	}

	Vector2f GetMousePosition()
	{
		int mouseX, mouseY;
		SDL_GetMouseState(&mouseX, &mouseY);
		return Vector2f(mouseX, mouseY);
	}
private:
	enum class KeyState
	{
		Nothing,
		JustDown,
		Up,
		Down
	};

	using keyIndex = int;
	map<keyIndex, KeyState> m_keyStates;
};

#endif