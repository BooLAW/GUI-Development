#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Input.h"
#include "j1Textures.h"
#include "j1Audio.h"
#include "j1Render.h"
#include "j1Window.h"
#include "j1Map.h"
#include "j1PathFinding.h"
#include "j1Gui.h"
#include "j1Scene.h"
#include "UI_Image.h"

j1Scene::j1Scene() : j1Module()
{
	name.create("scene");
}

// Destructor
j1Scene::~j1Scene()
{}

// Called before render is available
bool j1Scene::Awake()
{
	LOG("Loading Scene");
	bool ret = true;

	return ret;
}

// Called before the first frame
bool j1Scene::Start()
{
	if(App->map->Load("iso_walk.tmx") == true)
	{
		int w, h;
		uchar* data = NULL;
		if(App->map->CreateWalkabilityMap(w,h,&data))
			App->pathfinding->SetMap(w,h,data);
		RELEASE_ARRAY(data);
	}
	
	debug_tex = App->tex->Load("maps/path2.png");
	
	UI_Image* background;
	background->SetRect({ 0,0,800,800 });
	background->SetPos(0, 0);
	
	//UI_Window* screen = (UI_Window*)App->gui->Create_Element(WINDOW, { 0,0 }, {0,0,640,480}, App->gui->GetBackground(),-1,false,nullptr,nullptr);

	//UI_Label* win1_title = (UI_Label*)App->gui->Create_Element(LABEL, {400,200},);

	//UI_Label* button1_title = (UI_Label*)App->gui->Create_Element();

	//UI_Button* button1 = (UI_Button*)App->gui->Create_Element(BUTTON, {400,200}, {},App->gui->GetAtlas(),1,false,"button 1",nullptr);

	//UI_Window* win1 = (UI_Window*)App->gui->Create_Element(WINDOW, {350,150}, {},App->gui->GetAtlas(),2,false, "window 1",nullptr);
	
	//tree of GUI
	/*button1_title->parent = button1;

	button1->linked_elements.add(button1_title);
	button1->parent = win1;

	win1_title->parent = win1;

	win1->linked_elements.add(button1);
	win1->parent = screen;*/

	//screen->linked_elements.add(win1);
	//screen->parent = nullptr;//way to know the tree parent node	

	return true;
}

// Called each loop iteration
bool j1Scene::PreUpdate()
{

	// debug pathfing ------------------
	static iPoint origin;
	static bool origin_selected = false;

	int x, y;
	App->input->GetMousePosition(x, y);
	iPoint p = App->render->ScreenToWorld(x, y);
	p = App->map->WorldToMap(p.x, p.y);

	if(App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_DOWN)
	{
		if(origin_selected == true)
		{
			App->pathfinding->CreatePath(origin, p);
			origin_selected = false;
		}
		else
		{
			origin = p;
			origin_selected = true;
		}
	}

	return true;
}

// Called each loop iteration
bool j1Scene::Update(float dt)
{
	// Gui ---
	if (App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == true)
	{
		float speed = 67.0f;
		int x, y;
		App->input->GetMouseMotion(x, y);
		App->render->camera.x += (int)(speed * float(x) * dt);
		App->render->camera.y += (int)(speed * float(y) * dt);
	}

	



	// -------
	if(App->input->GetKey(SDL_SCANCODE_L) == KEY_DOWN)
		App->LoadGame("save_game.xml");

	if(App->input->GetKey(SDL_SCANCODE_S) == KEY_DOWN)
		App->SaveGame("save_game.xml");

	if(App->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT)
		App->render->camera.y += floor(200.0f * dt);

	if(App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT)
		App->render->camera.y -= floor(200.0f * dt);

	if(App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
		App->render->camera.x += floor(200.0f * dt);

	if(App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
		App->render->camera.x -= floor(200.0f * dt);

	App->map->Draw();

	int x, y;
	App->input->GetMousePosition(x, y);
	iPoint map_coordinates = App->map->WorldToMap(x - App->render->camera.x, y - App->render->camera.y);
	p2SString title("Map:%dx%d Tiles:%dx%d Tilesets:%d Tile:%d,%d",
					App->map->data.width, App->map->data.height,
					App->map->data.tile_width, App->map->data.tile_height,
					App->map->data.tilesets.count(),
					map_coordinates.x, map_coordinates.y);

	//App->win->SetTitle(title.GetString());

	// Debug pathfinding ------------------------------
	//int x, y;
	App->input->GetMousePosition(x, y);
	iPoint p = App->render->ScreenToWorld(x, y);
	p = App->map->WorldToMap(p.x, p.y);
	p = App->map->MapToWorld(p.x, p.y);

	App->render->Blit(debug_tex, p.x, p.y);

	const p2DynArray<iPoint>* path = App->pathfinding->GetLastPath();

	for(uint i = 0; i < path->Count(); ++i)
	{
		iPoint pos = App->map->MapToWorld(path->At(i)->x, path->At(i)->y);
		App->render->Blit(debug_tex, pos.x, pos.y);
	}
	return true;
}

// Called each loop iteration
bool j1Scene::PostUpdate()
{
	bool ret = true;

	if(App->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
		ret = false;

	return ret;
}

// Called before quitting
bool j1Scene::CleanUp()
{
	LOG("Freeing scene");
	
	return true;
}
