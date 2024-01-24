//SDL
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

//Standard library
#include <iostream>
#include <vector>
#include <memory>

//Physics engine
#include <SydPhysics.hpp>

//Game engine 
#include <Engine/RenderWindow.hpp>
#include <Engine/Entity.hpp>
#include <Engine/Input.hpp>

using namespace SydPhysics;
using namespace std;

int main(int argc, char* args[])
{
	//Initialize window
	if(SDL_Init(SDL_INIT_VIDEO) > 0)
		std::cout << "SDL_INIT HAS FAILED: SDL_ERROR: " << SDL_GetError() << std::endl;

	if(!(IMG_Init(IMG_INIT_PNG)))
		std::cout << "IMG_INIT HAS FAILED: SDL_ERROR: " << SDL_GetError() << std::endl;

	uint32_t mTickCount = 0;
	RenderWindow window("SydPhysics v1", 1280, 720);

	//Create physics world with custom settings
	PhysicsWorld::WorldSettings settings;
	settings.gravity = Vector2f();

	PhysicsWorld physicsWorld(settings);

	//Init entity list
	vector<unique_ptr<Entity>> newEntityList;

	//Load textures
	//Temp for demos
	SDL_Texture* boxTexture = window.loadTexture("res/gfx/testBox.png");
	SDL_Texture* sphereTexture = window.loadTexture("res/gfx/testCircle.png");

	//TODO: Create a nicer function for creation of objects
	//First sphere
	newEntityList.push_back(unique_ptr<Entity>(new Entity(Vector2f(-1,10), Vector2f(1,1), boxTexture)));
	SphereShape shape(1);
	PhysicsObject* specialObject = physicsWorld.CreatePhysicsObject(1, newEntityList[newEntityList.size()-1].get(), &shape, true);

	newEntityList.push_back(unique_ptr<Entity>(new Entity(Vector2f(0,0), Vector2f(0.5,0.5), sphereTexture)));

	//Create game variables
	bool gameRunning = true;

	//Create game handlers
	InputHandler inputHandler;
	SDL_Event event;

	Camera cam(Vector2f(-10,0), Vector2f());
	cam.SetScale(10);
	window.setCam(&cam);

	while(gameRunning)
	{
		float wheelScroll = 0;
		while(SDL_PollEvent(&event))
		{
			switch(event.type)
			{
				case SDL_QUIT:
					gameRunning = false;
					break;
				case SDL_KEYDOWN:
				case SDL_KEYUP:
					inputHandler.Update(&event);
					break;
				case SDL_MOUSEWHEEL:
					wheelScroll = event.wheel.y;
					break;
			}
		}

		//Clamp tickrate
		while(!SDL_TICKS_PASSED(SDL_GetTicks(), mTickCount + 16));

		//Get delta time
		float deltaTime = (SDL_GetTicks() - mTickCount) / 1000.0f;
		mTickCount = SDL_GetTicks();

		//Game loop
		//Test input stuff
		Vector2f wasdInput = inputHandler.TwoDMap(SDLK_w, SDLK_s, SDLK_a, SDLK_d);
		wasdInput = wasdInput * 100;
		cam.SetScale(cam.GetScale() + (wheelScroll * 20 * deltaTime));

		Vector2f worldMouse = inputHandler.GetMousePosition();
		worldMouse = cam.ScreenToWorldPosition(worldMouse);
		specialObject->AddForceAtPoint(worldMouse, wasdInput);

		newEntityList[1]->GetTransform()->SetPosition(worldMouse);
		
		//Testing out springs for fun
		Vector2f displacement = worldMouse - specialObject->GetTransform()->GetPosition();
		float k = 10;
		specialObject->AddForce(displacement*k);
		
		//Physics loop
		//Runs accel, velocity, and collisions
		physicsWorld.Update(deltaTime);
		
		//Render all objects
		window.clear();

		for(auto& e : newEntityList)
		{
			//Maybe fix this at some point idk you're your own person and stuff
			window.renderRot(*e.get());
		}

		window.display();
	}		

	window.cleanUp();
	SDL_Quit();

	return 0;
}