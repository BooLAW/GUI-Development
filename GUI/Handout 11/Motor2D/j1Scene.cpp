#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Input.h"
#include "j1Textures.h"
#include "j1Audio.h"
#include "j1Render.h"
#include "j1Window.h"
#include "j1Gui.h"
#include "j1Scene.h"
#include "j1Fonts.h"

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
	// TODO 3: Creating Elements ---------------------------
	Background = (Image*)App->gui->Create_Element("background", IMAGE, { 0, 0 }, { 970, 1844, 768, 579 } );
	
	Ken1 = (Image*)App->gui->Create_Element("ken1", IMAGE, { 24, 61 }, { 925, 884, 168, 279 });
	Ken2 = (Image*)App->gui->Create_Element("ken2", IMAGE, { 543, 61 }, { 925, 884, 168, 279 });

	Ryu1 = (Image*)App->gui->Create_Element("ryu1", IMAGE, { 24, 61 }, { 925, 605, 168, 279 });

	P1_Sel = (DynamicImage*)App->gui->Create_Element("P1selector", DYNAMICIMAGE, {240, 78}, { 1485, 110, 72, 109 });
	P2_Sel = (DynamicImage*)App->gui->Create_Element("P2selector", DYNAMICIMAGE, { 240, 172 }, { 1560, 110, 72, 109 });
	//Load Properties
	face_blanka = { 384, 78 };
	face_ryu = { 240, 78 };
	face_honda = { 312, 78 };
	face_guile = { 456, 78 };

	face_zangief = { 384, 174 };
	face_ken = { 240, 174 };
	face_chunli = { 312, 174 };
	face_dhalism = { 456, 174 };

	P1_Sel->positions->PushBack(face_ryu);
	P1_Sel->positions->PushBack(face_honda);
	P1_Sel->positions->PushBack(face_blanka);
	P1_Sel->positions->PushBack(face_guile);
	P1_Sel->positions->PushBack(face_ken);
	P1_Sel->positions->PushBack(face_chunli);
	P1_Sel->positions->PushBack(face_dhalism);
	P1_Sel->current_pos = 2;
	P1_Sel->view = true;
	

	P2_Sel->positions->PushBack(face_ryu);
	P2_Sel->positions->PushBack(face_honda);
	P2_Sel->positions->PushBack(face_blanka);
	P2_Sel->positions->PushBack(face_guile);
	P2_Sel->positions->PushBack(face_ken);
	P2_Sel->positions->PushBack(face_chunli);
	P2_Sel->positions->PushBack(face_dhalism);
	P2_Sel->current_pos = 5;
	P2_Sel->view = true;




	return true;
}

// Called each loop iteration
bool j1Scene::PreUpdate()
{
	return true;
}

// Called each loop iteration
bool j1Scene::Update(float dt)
{
	// -----------------------
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

	if (App->input->GetKey(SDL_SCANCODE_TAB) == KEY_REPEAT)
		p1 = !p1;
	
	// Gui ---------------------------------------------
	Background->Draw();
	Ken1->Draw();
	Ken2->Draw();
	if(p1)
		P1_Sel->MoveArrows();
	else
		P2_Sel->MoveArrows();

	P1_Sel->Draw();
	P2_Sel->Draw();

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
