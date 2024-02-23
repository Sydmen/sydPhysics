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
	WorldSettings settings;
	settings.gravity = Vector2f(0,30);
	settings.restitutionCoeffectient = 0.8;
	settings.awakeEpsilon = 0.1;

	PhysicsWorld physicsWorld(settings);

	//Init entity list
	vector<unique_ptr<Entity>> entityList;

	//Load textures
	//Temp for demos
	SDL_Texture* sphereTex = window.loadTexture("res/gfx/testCircle.png");
	SDL_Texture* boxTex = window.loadTexture("res/gfx/testBox.png");

	//if you're confused, plot this on desmos
	vector<Vector2f> triOneVerts{Vector2f(3,2), Vector2f(4,1), Vector2f(-4,1)};
	vector<Vector2f> triTwoVerts{Vector2f(-1,2), Vector2f(-4,2), Vector2f(-2,1)};

	/*newEntityList.push_back(unique_ptr<Entity>(new Entity(Vector2f(-1,10), Vector2f(1,1), sphereTex)));
	physicsWorld.CreatePhysicsObject(newEntityList[newEntityList.size()-1].get(), 1, SphereShape(1), true);*/

	// PolygonShape triOne(triOneVerts);
	// PolygonShape triTwo(triTwoVerts);

	// entityList.push_back(unique_ptr<Entity>(new Entity(Vector2f(-10,10), Vector2f(2,2), sphereTex)));
	// physicsWorld.CreatePhysicsObject(entityList[entityList.size()-1].get(), 1, &triOne, true);
	
	// entityList.push_back(unique_ptr<Entity>(new Entity(Vector2f(10,10), Vector2f(2,2), sphereTex)));
	// physicsWorld.CreatePhysicsObject(entityList[entityList.size()-1].get(), 1, &triTwo, true);

	AABBShape groundBox(Vector2f(100,5));
	AABBShape wallBox(Vector2f(1,100));
	SphereShape testSphere(1);
	
	entityList.push_back(unique_ptr<Entity>(new Entity(Vector2f(-10,10), Vector2f(2,2), sphereTex)));
	physicsWorld.CreatePhysicsObject(entityList[entityList.size()-1].get(), 2, &testSphere, true);

	// entityList.push_back(unique_ptr<Entity>(new Entity(Vector2f(-9,0), Vector2f(2,2), sphereTex)));
	// physicsWorld.CreatePhysicsObject(entityList[entityList.size()-1].get(), 1, &testSphere, true);
	
	entityList.push_back(unique_ptr<Entity>(new Entity(Vector2f(0,50), Vector2f(200,10), boxTex)));
	physicsWorld.CreatePhysicsObject(entityList[entityList.size()-1].get(), 0, &groundBox, false);

	entityList.push_back(unique_ptr<Entity>(new Entity(Vector2f(-80,-20), Vector2f(2,200), boxTex)));
	physicsWorld.CreatePhysicsObject(entityList[entityList.size()-1].get(), 0, &wallBox, false);

	entityList.push_back(unique_ptr<Entity>(new Entity(Vector2f(80,-20), Vector2f(2,200), boxTex)));
	physicsWorld.CreatePhysicsObject(entityList[entityList.size()-1].get(), 0, &wallBox, false);

	//Create game variables
	bool gameRunning = true;

	//Create game handlers
	InputHandler inputHandler;
	SDL_Event event;
	
	Camera cam(Vector2f(0,-10), Vector2f());
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
		wasdInput = wasdInput * 100;
		cam.SetScale(cam.GetScale() + (wheelScroll * 20 * deltaTime));

		Vector2f newCamPos = cam.GetTransform().GetPosition() + wasdInput * deltaTime;
		cam.GetTransform().SetPosition(newCamPos);

		Vector2f mousePosition = inputHandler.GetMousePosition();
		mousePosition = cam.ScreenToWorldPosition(mousePosition);
		//specialObject->SetVelocity((mousePosition - specialObject->GetTransform().GetPosition())*10);

		if(inputHandler.KeyDown(SDLK_SPACE))
		{	
			float randomX = (rand()/1000) % 5;
			entityList.push_back(unique_ptr<Entity>(new Entity(Vector2f(mousePosition.x+randomX,mousePosition.y), Vector2f(2,2), sphereTex)));

			entityList[entityList.size()-1].get()->r = rand() % 255;
			entityList[entityList.size()-1].get()->g = rand() % 255;
			entityList[entityList.size()-1].get()->b = rand() % 255;
			
			PhysicsObject* newObj = physicsWorld.CreatePhysicsObject(entityList[entityList.size()-1].get(), 1, &testSphere, true);

			newObj->SetVelocity((mousePosition-lastMousePos)*10);
		}

		lastMousePos = mousePosition;

		//Physics loop
		physicsWorld.Update(deltaTime);

		// triOne.draw(window);
		// triTwo.draw(window);
		// triOne.setVert(2, mousePosition);

		// if(PolyVsPolyAlgorithm::Collides(triOne, triTwo))
		// {
		// 	window.drawLine(Vector2f(2,2), Vector2f(5,5));
		// }

		for(auto& e : entityList)
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