//SDL

//STOP THROWING STUPID ERROS
//YOU DO KNOW WHERE SDL IS!!!!!!!!!!!!
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

int main(int argv, char** args)
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

	PhysicsWorld physicsWorld(settings);

	//Init entity list
	vector<unique_ptr<Entity>> newEntityList;

	//Load textures
	//Temp for demos
	SDL_Texture* sphereTex = window.loadTexture("res/gfx/testCircle.png");
	SDL_Texture* boxTex = window.loadTexture("res/gfx/testBox.png");

	//TODO: Create a nicer function for creation of objects
	//First sphere
	vector<Vector2f> testVerts{Vector2f(1,1), Vector2f(-1,1), Vector2f(-1,-1), Vector2f(1,-1)};

	/*newEntityList.push_back(unique_ptr<Entity>(new Entity(Vector2f(-1,10), Vector2f(1,1), sphereTex)));
	physicsWorld.CreatePhysicsObject(newEntityList[newEntityList.size()-1].get(), 1, SphereShape(1), true);*/

	SphereShape testShape(1);
	newEntityList.push_back(unique_ptr<Entity>(new Entity(Vector2f(-10,10), Vector2f(2,2), sphereTex)));
	physicsWorld.CreatePhysicsObject(newEntityList[newEntityList.size()-1].get(), 1, &testShape, true);
	
	AABBShape testingShapes(Vector2f(50,1));
	newEntityList.push_back(unique_ptr<Entity>(new Entity(Vector2f(-10,20), Vector2f(100,2), boxTex)));
	physicsWorld.CreatePhysicsObject(newEntityList[newEntityList.size()-1].get(), 0, &testingShapes, false);

	//Create game variables
	bool gameRunning = true;

	//Create game handlers
	InputHandler inputHandler;
	SDL_Event event;

	Camera cam(Vector2f(-30,-10), Vector2f());
	cam.SetScale(20);
	window.setCam(&cam);

	float timer = 0;

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

		//Clear out current window
		window.clear();

		//Game loop
		//Test input stuff
		Vector2f wasdInput = inputHandler.TwoDMap(SDLK_w, SDLK_s, SDLK_a, SDLK_d);
		wasdInput = wasdInput * 100;
		cam.SetScale(cam.GetScale() + (wheelScroll * 20 * deltaTime));

		Vector2f newCamPos = cam.GetTransform().GetPosition() + wasdInput * deltaTime;
		cam.GetTransform().SetPosition(newCamPos);

		Vector2f mousePosition = inputHandler.GetMousePosition();
		mousePosition = cam.ScreenToWorldPosition(mousePosition);
		//specialObject->SetVelocity((mousePosition - specialObject->GetTransform().GetPosition())*10);

		timer += deltaTime;
		if(timer > 0.1)
		{
			float offset = rand() % 10;
			newEntityList.push_back(unique_ptr<Entity>(new Entity(Vector2f(-10+offset,10), Vector2f(2,2), sphereTex)));
			physicsWorld.CreatePhysicsObject(newEntityList[newEntityList.size()-1].get(), 1, &testShape, true);

			timer = 0;
		}

		//Physics loop
		//Runs accel, velocity, and collisions
		physicsWorld.Update(deltaTime);

		for(auto& e : newEntityList)
		{
			//Maybe fix this at some point idk you're your own person and stuff
			window.renderRot(*e.get());
		}

		//window.drawLine(newEntityList[1]->GetTransform().GetPosition(), specialObject->GetTransform().GetPosition());

		window.display();
	}		

	window.cleanUp();
	SDL_Quit();

	return 0;
}