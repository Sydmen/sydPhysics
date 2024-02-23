#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <Engine/Entity.hpp>

Entity::Entity(Vector2f p_pos, Vector2f p_scale)
:tex(nullptr)
{
	transform = Transform(p_pos);
}

Entity::Entity(Vector2f p_pos, Vector2f p_scale, SDL_Texture* p_tex)
:tex(p_tex)
{
	transform = Transform(p_pos, p_scale);
	
	currentFrame.x = 0;
	currentFrame.y = 0;
	
	//How large is a single pixel?
	currentFrame.w = 10;
	currentFrame.h = 10;

	r = 255;
	g = 255;
	b = 255;
}

Transform& Entity::GetTransform()
{
	return transform;
}

SDL_Texture* Entity::getTex()
{
	return tex;
}

SDL_Rect Entity::getCurrentFrame()
{
	return currentFrame;
}