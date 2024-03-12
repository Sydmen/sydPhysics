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
	if(p_entity.getTex() == nullptr) return;

	Vector2f camPos = activeCamera->GetTransform().GetPosition();
	float camScale = activeCamera->GetScale();
	
	Transform& entityTransform = p_entity.GetTransform();	
	Vector2f entPos = entityTransform.GetPosition();
	Vector2f entScale = entityTransform.GetScale();

	//Force render to center on its transform orgin
	SDL_Rect dest;	
	dest.x = ((entPos.x - entScale.x/2) - camPos.x) * camScale;
	dest.y = ((entPos.y - entScale.y/2) - camPos.y) * camScale;
	dest.w = entScale.x * camScale;
	dest.h = entScale.y * camScale;
	
	SDL_RenderCopy(renderer, p_entity.getTex(), NULL, &dest);
}

void RenderWindow::renderRot(Entity& p_entity)
{
	if(p_entity.getTex() == nullptr) return;
	
	//Get camera pos and scale
	Vector2f camPos = activeCamera->GetTransform().GetPosition();
	float camScale = activeCamera->GetScale();
	
	//Get entity pos and scale
	Transform& entityTransform = p_entity.GetTransform();	
	Vector2f entPos = entityTransform.GetPosition();
	Vector2f entScale = entityTransform.GetScale();

	//Render, using orgin as center
	SDL_Rect dest;	
	dest.x = ((entPos.x - entScale.x/2) - camPos.x) * camScale;
	dest.y = ((entPos.y - entScale.y/2) - camPos.y) * camScale;
	dest.w = entScale.x * camScale;
	dest.h = entScale.y * camScale;
	
	SDL_SetTextureColorMod(p_entity.getTex(), p_entity.r, p_entity.g, p_entity.b);
	SDL_RenderCopyEx(renderer, p_entity.getTex(), NULL, &dest, entityTransform.GetRotation(), NULL, SDL_FLIP_NONE);
}

void RenderWindow::drawLine(Vector2f posA, Vector2f posB)
{
	posA = activeCamera->WorldToScreenPosition(posA);
	posB = activeCamera->WorldToScreenPosition(posB);

	SDL_SetRenderDrawColor(renderer, 255,255,255,1);
	SDL_RenderDrawLine(renderer, posA.x, posA.y, posB.x, posB.y);
	SDL_SetRenderDrawColor(renderer, 0,0,0,1);
}

void RenderWindow::drawLine(Vector2f posA, Vector2f posB, float r, float g, float b)
{
	posA = activeCamera->WorldToScreenPosition(posA);
	posB = activeCamera->WorldToScreenPosition(posB);

	SDL_SetRenderDrawColor(renderer, r,g,b,1);
	SDL_RenderDrawLine(renderer, posA.x, posA.y, posB.x, posB.y);
	SDL_SetRenderDrawColor(renderer, 0,0,0,1);
}

void RenderWindow::drawPolyShape(PhysicsObject* obj)
{
	if(obj->GetCollider()->shapeType != ShapeType::POLY) return;
	PolygonShape* shape = (PolygonShape*)obj->GetCollider();
	Vector2f pos = obj->GetTransform().GetPosition();

	//draw edges
	int n = shape->verts.size();
	drawLine(shape->verts[n-1] + pos,shape->verts[0] + pos, 0, 255, 0);

	for(int i = 1; i < n; i++)
	{
		drawLine(shape->verts[i-1] + pos, shape->verts[i] + pos);
	}

	//draw normals
	Vector2f half = (shape->verts[n-1]+shape->verts[0])/2;
	drawLine(half + pos,(half+shape->normals[0]) + pos, 255, 0, 0);
	
	for(int i = 1; i < n; i++)
	{
		half = (shape->verts[i-1]+shape->verts[i])/2;
		drawLine(half + pos,(half+shape->normals[i]) + pos, 255, 0, 0);
	}
}

void RenderWindow::display()
{
	SDL_RenderPresent(renderer);
}