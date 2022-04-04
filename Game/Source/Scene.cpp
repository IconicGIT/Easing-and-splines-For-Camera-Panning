#include "App.h"
#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"
#include "Scene.h"

#include "Defs.h"
#include "Log.h"
#include "ModuleFonts.h"
#include <stdio.h>

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720

Scene::Scene() : Module()
{
	name.Create("scene");
}

// Destructor
Scene::~Scene()
{}

// Called before render is available
bool Scene::Awake()
{
	LOG("Loading Scene");
	bool ret = true;

	return ret;
}

// Called before the first frame
bool Scene::Start()
{
	map = app->tex->Load("Assets/Textures/map.png");
	app->render->camera.x = cameraX = -1280 + WINDOW_WIDTH / 2;
	app->render->camera.y = cameraY = -1040 + WINDOW_HEIGHT / 2;
	player.Set(1280, 1280, 40, 120);
	player.speed = 4;

	sn_activatePanning.Set(1282 + 30, 1026 + 30, 60, 60);

	tw_cameraPanning.Set();
	tw_cameraPanning.smoothness = 4;
	tw_cameraPanning.AddTween(100, 200, EXPONENTIAL_IN_OUT);
	tw_cameraPanning.AddTween(100, 100, EXPONENTIAL_IN_OUT);
	tw_cameraPanning.AddTween(200, 200, EXPONENTIAL_IN_OUT);
	tw_cameraPanning.AddTween(200, 100, EXPONENTIAL_IN_OUT);
	tw_cameraPanning.AddTween(300, 200, EXPONENTIAL_IN_OUT);
	tw_cameraPanning.AddTween(300, 100, EXPONENTIAL_IN_OUT);
	tw_cameraPanning.AddTween(400, 200, EXPONENTIAL_IN_OUT);
	tw_cameraPanning.AddTween(400, 100, EXPONENTIAL_IN_OUT);
	tw_cameraPanning.AddTween(500, 100, EXPONENTIAL_IN_OUT);
	tw_cameraPanning.AddTween(500, 100, EXPONENTIAL_IN_OUT);

	//tw_cameraPanning.AddTween(200, 100, QUADRATIC_IN_OUT);
	
	



	tw_cameraPanning.Backward();
	panning = false;

	return true;
}

// Called each loop iteration
bool Scene::PreUpdate()
{

	return true;
}

// Called each loop iteration
bool Scene::Update(float dt)
{
	app->render->DrawTexture(map, 0, 0,1,1);
	tw_cameraPanning.Step(1,false);


	if (!panning)
	{
		if (app->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
		{
			player.x += player.speed;
		}
		if (app->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
		{
			player.x -= player.speed;

		}
		if (app->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT)
		{
			player.y -= player.speed;

		}
		if (app->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT)
		{
			player.y += player.speed;

		}
	}

	if (sn_activatePanning.Triggered(player.x,player.y))
	{
		panning = true;
		tw_cameraPanning.Foward();
	}
	else
	{
		tw_cameraPanning.JumpTo(0,false);
		tw_cameraPanning.Backward();
		panning = false;
	}

	LOG("p %f", tw_cameraPanning.GetPoint());
	if (panning)
	{
		float value_camera_panning = tw_cameraPanning.GetPoint();

		if (value_camera_panning <= 1 && value_camera_panning > 0)
		{
			
			app->render->camera.x = cameraX + value_camera_panning * (-cameraX + WINDOW_WIDTH/2 - 700) ;
			app->render->camera.y = cameraY + value_camera_panning * (-cameraY + WINDOW_HEIGHT/ 2 - 450);
		
			if (value_camera_panning == 1)
			{
				cameraX = app->render->camera.x;
				cameraY = app->render->camera.y;
			}
		}
		else if (value_camera_panning <= 2 && value_camera_panning > 1)
		{

			//app->render->camera.x = cameraX + value_camera_panning * (-cameraX + WINDOW_WIDTH / 2 - 700);
			app->render->camera.y = cameraY + (value_camera_panning - 1) * (-cameraY + WINDOW_HEIGHT / 2 - 1700);
		
			
			if (value_camera_panning == 2)
			{
				cameraX = app->render->camera.x;
				cameraY = app->render->camera.y;
			}
		}
		else if(value_camera_panning <= 3 && value_camera_panning > 2)
		{

			app->render->camera.x = cameraX + (value_camera_panning - 2) * (-cameraX + WINDOW_WIDTH / 2 - 1900);
			//app->render->camera.y = cameraY + (value_camera_panning - 1) * (-cameraY + WINDOW_HEIGHT / 2 - 1700);
		
		
			if (value_camera_panning == 3)
			{
				cameraX = app->render->camera.x;
				cameraY = app->render->camera.y;
			}
		}
		else if(value_camera_panning <= 4 && value_camera_panning > 3)
		{

			//app->render->camera.x = cameraX + (value_camera_panning - 3) * (-cameraX + WINDOW_WIDTH / 2 - 700);
			app->render->camera.y = cameraY + (value_camera_panning - 3) * (-cameraY + WINDOW_HEIGHT / 2 - 450);
		
		
			if (value_camera_panning == 4)
			{
				cameraX = app->render->camera.x;
				cameraY = app->render->camera.y;
			}
		}
		else if (value_camera_panning <= 5 && value_camera_panning > 4)
		{
			app->render->camera.x = cameraX + (value_camera_panning - 4) * (-cameraX + WINDOW_WIDTH / 2 - 1280);
			app->render->camera.y = cameraY + (value_camera_panning - 4) * (-cameraY + WINDOW_HEIGHT / 2 - 1040);


			if (value_camera_panning == 5)
			{
				cameraX = app->render->camera.x;
				cameraY = app->render->camera.y;
			}
		}
		
		if (tw_cameraPanning.Progress() == 1) panning = false;

	}

	player.Draw(255, 255, 255);
	sn_activatePanning.Draw(100,255,100);

	/*LOG("p %f", tw_cameraPanning.GetPoint());
	LOG("d %i", tw_cameraPanning.Main().duration());*/

	return true;
}

// Called each loop iteration
bool Scene::PostUpdate()
{
	bool ret = true;

	if(app->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
		ret = false;

	return ret;
}

// Called before quitting
bool Scene::CleanUp()
{
	LOG("Freeing scene");

	return true;
}
