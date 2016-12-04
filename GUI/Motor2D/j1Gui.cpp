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
	p2List_item<UI_Element*>* item;

	for (item = elements.start; item; item = item->next)
		RELEASE(item->data);

	elements.clear();

	return true;
}

// const getter for atlas
 SDL_Texture* j1Gui::GetAtlas() const
{
	return atlas;
}
 SDL_Texture* j1Gui::GetBackground() const
 {
	 return background;
 }

// class Gui ---------------------------------------------------

//----MANAGER----
UI_Element* j1Gui::Create_Element(TYPE _type, iPoint _pos, SDL_Rect _rect, SDL_Texture* _texture, uint _tab_id, bool _active, char* _text, _TTF_Font* _text_font)
{
	if (_type == BUTTON)
	{
		UI_Button* ret = new UI_Button(_type, _pos, _rect, _texture, _tab_id, _active);
		elements.add(ret);
		return ret;
	}
	else if (_type == WINDOW)
	{
		UI_Window* ret = new UI_Window(_type, _pos, _rect, _texture,_tab_id,_active);
		elements.add(ret);
		return ret;
	}
	else if (_type == BACKGROUND)
	{
		UI_Background* ret = new UI_Background(_type, _pos, _rect, _texture);
		elements.add(ret);
		return ret;
	}
	else if (_type == LABEL)
	{
		UI_Label* ret = new UI_Label(_type, _pos, _rect, _texture, _tab_id, _active,_text,_text_font);
		elements.add(ret);
		return ret;
	}else
		return nullptr;	
}

void UI_Element::SetPos(int x, int y)
{
	pos.x = x;
	pos.y = y;
}

iPoint UI_Element::GetPos()const
{
	if (parent != nullptr)
	{
		//the position is set respect the parent, so:
		return iPoint(pos.x + parent->pos.x, pos.y + parent->pos.y);
	}
	else
	{
		return iPoint(pos.x, pos.y);
	}
}
void UI_Element::SetRect(SDL_Rect _rect)
{
	rect = _rect;
}

void UI_Element::SetParent(UI_Element* _parent)
{
	parent = _parent;
}

//---Interactive_element functions----------------

bool UI_Interactive_element::IsOnTop()
{
	bool ret = false;
	iPoint mouse;
	App->input->GetMousePosition(mouse.x, mouse.y);
	if ((mouse.y > rect.y) && (mouse.x > rect.x) && (mouse.x < rect.x + rect.w) && (mouse.y < rect.y + rect.h))
		ret = true;
	else
		ret = false;

	return ret;
}

bool UI_Interactive_element::RightClicked()
{
	bool ret = false;
	if (IsOnTop() && App->input->GetMouseButtonDown(RI_MOUSE_RIGHT_BUTTON_DOWN));
		ret = true;
	return ret;
}

bool UI_Interactive_element::LeftClicked()
{
	bool ret = false;
	if (IsOnTop() && App->input->GetMouseButtonDown(RI_MOUSE_LEFT_BUTTON_DOWN)==true);
		ret = true;
	return ret;
}

void UI_Interactive_element::Handle_Input()
{
	if (RightClicked())
	{
		r_clicked = true;
		l_clicked = false;
		hovering = false;
	}
	else if (LeftClicked())
	{
		r_clicked = false;
		l_clicked = true;
		hovering = false;
	}
	else if (IsOnTop())
	{
		r_clicked = false;
		l_clicked = false;
		hovering = true;
	}
	else
	{
		r_clicked = false;
		l_clicked = false;
		hovering = false;
	}
}

//---Updates-------------------

void UI_Label::Update()
{
	SDL_Texture* L = App->font->Print(text.GetString(), {255,255,255}, text_font);
	App->render->Blit(L, 200, 300, &rect);
}