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
	RenderWindow window("SydPhysics", 1280, 720);

	//Create physics world with custom settings
	PhysicsWorldSettings settings;
	settings.gravity = Vector2f();
	settings.restitutionCoeffectient = 0.5;
	settings.awakeEpsilon = 0;
	
	PhysicsWorld physicsWorld(settings);

	//Init entity list
	vector<unique_ptr<Entity>> entityList;

	//Load textures
	//SDL_Texture* boxTex = window.loadTexture("res/gfx/testBox.png");

	vector<Vector2f> boxVerts{Vector2f(1,1), Vector2f(-1,1), Vector2f(-1,-2), Vector2f(1,-1)};

	PolygonShape polyShape(boxVerts);
	PolygonShape otherPolyShape(boxVerts);

	entityList.push_back(unique_ptr<Entity>(new Entity(Vector2f(0,0), Vector2f(2,2), nullptr)));
	PhysicsObject* specialObject = physicsWorld.CreatePhysicsObject(entityList[entityList.size()-1].get(), 1, &polyShape, true);

	entityList.push_back(unique_ptr<Entity>(new Entity(Vector2f(-3,0), Vector2f(2,2), nullptr)));
	PhysicsObject* otherSpecialObject = physicsWorld.CreatePhysicsObject(entityList[entityList.size()-1].get(), 1, &otherPolyShape, true);

	//Create game variables
	bool gameRunning = true;

	//Create game handlers
	InputHandler inputHandler;
	SDL_Event event;
	
	Camera cam(Vector2f(-10,-10), Vector2f());
	cam.SetScale(10);
	window.setCam(&cam);

	Vector2f lastMousePos = inputHandler.GetMousePosition();
	lastMousePos = cam.ScreenToWorldPosition(lastMousePos);

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
		wasdInput = wasdInput * 10 * deltaTime;

		Vector2f mousePosition = inputHandler.GetMousePosition();
		mousePosition = cam.ScreenToWorldPosition(mousePosition);
		
		specialObject->AddForce(wasdInput);

		window.drawPolyShape(specialObject);
		window.drawPolyShape(otherSpecialObject);

		CollisionInfo info;	
		if(PolyVsPolyAlgorithm::TestCollision(polyShape, specialObject->GetTransform(), otherPolyShape, otherSpecialObject->GetTransform(), info)==true)
		{
			window.drawLine(Vector2f(0,0), Vector2f(5,5));
		}
		else
		{
			window.drawLine(Vector2f(0,0), Vector2f(5,0));
		}
		
		cam.SetScale(cam.GetScale() + (wheelScroll * 20 * deltaTime));

		//Physics loop
		physicsWorld.Update(deltaTime);

		for(auto& e : entityList)
		{
			window.renderRot(*e.get());
		}

		window.display();
	}		

	window.cleanUp();
	SDL_Quit();

	return 0;
}