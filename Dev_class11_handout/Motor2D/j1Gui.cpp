#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Render.h"
#include "j1Textures.h"
#include "j1Fonts.h"
#include "j1Input.h"
#include "j1Gui.h"


j1Gui::j1Gui() : j1Module()
{
	name.create("gui");
}

// Destructor
j1Gui::~j1Gui()
{}

// Called before render is available
bool j1Gui::Awake(pugi::xml_node& conf)
{
	LOG("Loading GUI atlas");
	bool ret = true;

	atlas_file_name = conf.child("atlas").attribute("file").as_string("");
	background_file_name = conf.child("background").attribute("file").as_string("");
	return ret;
}

// Called before the first frame
bool j1Gui::Start()
{
	atlas = App->tex->Load(atlas_file_name.GetString());
	background = App->tex->Load(background_file_name.GetString());
	return true;
}

// Update all guis
bool j1Gui::PreUpdate()
{
	return true;
}

// Called after all Updates
bool j1Gui::PostUpdate()
{
	return true;
}

// Called before quitting
bool j1Gui::CleanUp()
{
	LOG("Freeing GUI");

	return true;
}

// const getter for atlas
const SDL_Texture* j1Gui::GetAtlas() const
{
	return atlas;
}

// class Gui ---------------------------------------------------

//----MANAGER----
UI_Element* j1Gui::Create_Element(TYPE mytype)
{
	UI_Element* ret = new UI_Element();
	ret->type = mytype;
	return ret;
}
UI_Element* j1Gui::Destroy_Element(uint id)
{
	UI_Element* ret = nullptr;
	if (id >= elements.Count())
	{
		 ret = elements[id];
		delete elements[id];
	}
	return ret;
}
//
bool Interactive_element::IsOnTop()
{
	bool ret = false;
	iPoint mouse;
	if ((mouse.y > rect.y) && (mouse.x > rect.x) && (mouse.x < rect.x + rect.w) && (mouse.y < rect.y + rect.h))
		ret = true;
	else
		ret = false;

	return ret;
}

bool Interactive_element::RightClicked()
{
	bool ret = false;
	if (IsOnTop() && App->input->GetMouseButtonDown(RI_MOUSE_RIGHT_BUTTON_DOWN));
	{

	}
	return ret;
}
