#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

#include <Engine/RenderWindow.hpp>
#include <Engine/Entity.hpp>
#include <Engine/Camera.hpp>

RenderWindow::RenderWindow(const char* p_title, int p_w, int p_h)
	:window(NULL), renderer(NULL)
{
	window = SDL_CreateWindow(p_title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, p_w, p_h, SDL_WINDOW_SHOWN);

	if(window == NULL)
	{
		std::cout << "Window failed to create. Error: " << SDL_GetError() << std::endl;
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
}

SDL_Texture* RenderWindow::loadTexture(const char* p_filePath)
{
	SDL_Texture* texture = NULL;
	texture = IMG_LoadTexture(renderer, p_filePath);

	if(texture == NULL)
		std::cout << "Failed to load a texture. Error: " << SDL_GetError() << std::endl;

	return texture;
}

void RenderWindow::cleanUp()
{
	SDL_DestroyWindow(window);
}

void RenderWindow::clear()
{
	SDL_RenderClear(renderer);
}

void RenderWindow::setCam(Camera* camera)
{
	activeCamera = camera;
}

void RenderWindow::render(Entity& p_entity)
{
	Vector2f camPos = activeCamera->GetTransform()->GetPosition();
	float camScale = activeCamera->GetScale();
	
	Transform* entityTransform = p_entity.GetTransform();	
	Vector2f entPos = entityTransform->GetPosition();
	Vector2f entScale = entityTransform->GetScale();

	//Not doing tile map shit so don't use this
	
	/*SDL_Rect src;
	src.x = p_entity.getCurrentFrame().x;
	src.y = p_entity.getCurrentFrame().y;
	src.w = p_entity.getCurrentFrame().w;
	src.h = p_entity.getCurrentFrame().h;
*/
	//Position to write to on the screen
	//IMPORTANT
	//Currently forcing render to center on its transform orgin
	SDL_Rect dest;	
	dest.x = ((entPos.x - entScale.x/2) - camPos.x) * camScale;
	dest.y = ((entPos.y - entScale.y/2) - camPos.y) * camScale;
	dest.w = entScale.x * camScale;
	dest.h = entScale.y * camScale;
	
	SDL_RenderCopy(renderer, p_entity.getTex(), NULL, &dest);
}

void RenderWindow::renderRot(Entity& p_entity)
{
	//Get camera pos and scale
	Vector2f camPos = activeCamera->GetTransform()->GetPosition();
	float camScale = activeCamera->GetScale();
	
	//Get entity pos and scale
	Transform* entityTransform = p_entity.GetTransform();	
	Vector2f entPos = entityTransform->GetPosition();
	Vector2f entScale = entityTransform->GetScale();

	//Render, using orgin as center
	SDL_Rect dest;	
	dest.x = ((entPos.x - entScale.x/2) - camPos.x) * camScale;
	dest.y = ((entPos.y - entScale.y/2) - camPos.y) * camScale;
	dest.w = entScale.x * camScale;
	dest.h = entScale.y * camScale;
	
	SDL_RenderCopyEx(renderer, p_entity.getTex(), NULL, &dest, entityTransform->GetRotation(), NULL, SDL_FLIP_NONE);
}

void RenderWindow::display()
{
	SDL_RenderPresent(renderer);
}