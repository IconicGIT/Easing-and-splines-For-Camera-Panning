#ifndef __SCENE_H__
#define __SCENE_H__

#include "Module.h"
#include "Tweening.h"

struct SDL_Texture;

class BasicPlayer
{
public:
	BasicPlayer()
	{
		x = 0, y = 0;
	}
	~BasicPlayer() {}

	void Set(int x, int y, int w, int h)
	{
		x -= w / 2;
		y -= h / 2;

		this->x = x;
		this->y = y;
		this->w = w;
		this->h = h;


	}

	void Draw(int r, int g, int b)
	{

		SDL_Rect playerRect = { x - w/2,y - h/4 * 3,w,h };
		app->render->DrawRectangle(playerRect, 255, 255, 255, 180);
		app->render->DrawCircle(x + app->render->camera.x, y + app->render->camera.y, 3, 255, 255, 255, 180, false);

	}

	int x, y, w, h;
	float speed;

private:
};

class Sensor
{
public:
	Sensor()
	{
		x = 0, y = 0, w = 0, h = 0;
	}
	~Sensor() {}
	void Set(int x, int y, int w, int h)
	{
		x -= w / 2;
		y -= h / 2;

		this->x = x;
		this->y = y;
		this->w = w;
		this->h = h;
		rect = { x,y,w,h };

	}
	bool Triggered(int x_, int y_)
	{
		if ((x_ > x - w/2 && x_ < x + w) &&
			(y_ > y - h/2 && y_ < y + h))
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	void Draw(int r, int g, int b)
	{
		app->render->DrawRectangle(rect, r, g, b, 128, true);
	}


private:
	int x, y, w, h;
	SDL_Rect rect;
};


class UIelement
{
public:
	UIelement()
	{
		x = 0, y = 0, w = 0, h = 0;
	}
	~UIelement() {}

	void Set(int x, int y, int w, int h)
	{
		x -= w / 2;
		y -= h / 2;

		this->x = x;
		this->y = y; 
		this->w = w;
		this->h = h;
		
		
	}

	
	int x, y, w, h;
	


private:
	
};
class UIbutton : public UIelement
{
public:
	UIbutton() : clicked(false) {}
	~UIbutton(){}
	bool OnMouseOver() 
	{

		int x_, y_;
		app->input->GetMousePosition(x_, y_);
		if (x_ > x && x_ < (x + w) &&
			y_ > y && y_ < (y + h))
		{
			return true;
		}
		else return false;
	}

	bool OnMouseDown()
	{
		if (app->input->GetMouseButtonDown(SDL_BUTTON_LEFT))
		{
			clicked = true;
			return true;
		}
		else return false;
	}

	bool OnMouseRelease()
	{
		if (!app->input->GetMouseButtonDown(SDL_BUTTON_LEFT) && clicked)
		{
			clicked = false;
			return true;
		}
		else return false;
	}
private:

	bool clicked;
};

class Scene : public Module
{
public:

	Scene();

	// Destructor
	virtual ~Scene();

	// Called before render is available
	bool Awake();

	// Called before the first frame
	bool Start();

	// Called before all Updates
	bool PreUpdate();

	// Called each loop iteration
	bool Update(float dt);

	// Called before all Updates
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();

private:
	
	SDL_Texture* map;
	BasicPlayer player;

	Sensor sn_activatePanning;
	Tween tw_cameraPanning;

	Tween tw_playerLookingUp;
	Tween tw_playerLookingDown;
	Tween tw_playerLookingLeft;
	Tween tw_playerLookingRight;

	bool panning;
	int cameraX;
	int cameraY;


};




#endif // __SCENE_H__