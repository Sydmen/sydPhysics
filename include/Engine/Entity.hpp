#ifndef SYDPHYSICS_ENTITY_H
#define SYDPHYSICS_ENTITY_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <Math/Mathematics.hpp>

using namespace SydPhysics;

class Entity
{
public:
	//Constructors
	Entity(Vector2f p_pos, Vector2f p_scale);
	Entity(Vector2f p_pos, Vector2f p_scale, SDL_Texture* p_tex);
	~Entity(){};

	Transform* GetTransform();

	//Other stuff
	SDL_Texture* getTex();
	SDL_Rect getCurrentFrame();
protected:
	Transform transform;
	Vector2f pos;
	SDL_Rect currentFrame;
	SDL_Texture* tex;
};

#endif