#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <Engine/Entity.hpp>
#include <Engine/Camera.hpp>

class RenderWindow
{
public:
	RenderWindow(const char* p_title, int p_w, int p_h);
	SDL_Texture* loadTexture(const char* p_filePath);
	void cleanUp();
	void clear();
	void setCam(Camera* camera);

	//Normal render
	void render(Entity& p_entity);

	//Render with rotation
	void renderRot(Entity& p_entity);
	void display();
private:
	SDL_Window* window;
	SDL_Renderer* renderer;
	Camera* activeCamera;
};