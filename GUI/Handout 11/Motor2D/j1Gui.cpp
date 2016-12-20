#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Render.h"
#include "j1Textures.h"
#include "j1Fonts.h"
#include "j1Input.h"
#include "j1Gui.h"
#include "j1Scene.h"
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

	return ret;
}

// Called before the first frame
bool j1Gui::Start()
{
	atlas = App->tex->Load("gui/sf2.png");

	return true;
}

// Update all guis
bool j1Gui::PreUpdate()
{
	for (int i = 0; i < elements.Count(); i++)
	{
		elements[i]->Update();
	}

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

Element* j1Gui::Create_Element(const char* name, TYPE type, iPoint pos, SDL_Rect rect, p2SString text, _TTF_Font* font)
{
	Element* new_element = nullptr;

	if (type != LABEL && type != TEXT_BOX)
	{
		SDL_Texture* texture = (SDL_Texture*)App->gui->GetAtlas();

		if (type == IMAGE)
			new_element = new Image(name, pos, texture, rect);

		if (type == BUTTON)
			new_element = new Button(name, pos, texture, rect);

		if (type == WINDOW)
			new_element = new Window(name, pos, texture, rect);

		if(type == DYNAMICIMAGE)
			new_element = new DynamicImage(name, pos, texture, rect);

	}
	else
	{
		SDL_Texture* texture = App->font->Print(text.GetString(), font, rect.w, rect.h);

		if (type == LABEL)
			new_element = new Label(name, pos, texture, rect, text);

		if (type == TEXT_BOX)
			new_element = new Text_Box(name, pos, texture, rect, text);
	}
		
	elements.PushBack(new_element);
	return new_element;
}

void j1Gui::Destroy_Element(const char* name)
{
	for (int i = 0; i < elements.Count(); i++)
		if(elements[i]->name == name)
			delete (elements[i]);
}

bool j1Gui::Element_Moving()
{
	bool ret = false;

	for (int i = 0; i < elements.Count(); i++)
		if (elements[i]->moving == true) ret = true;

	return ret;
}

// ================================================================================

// Element ------------------------------------------------------------------------

Element::Element(const char* name, TYPE type, iPoint pos, SDL_Texture* texture, SDL_Rect rect) : name(name), type(type), pos(pos), texture(texture), rect(rect)
{}

Element::~Element()
{}

// Image -------------------------------------------------------------------------

Image::Image(const char* name, iPoint pos, SDL_Texture* texture, SDL_Rect rect) : Element(name, IMAGE, pos, texture, rect)
{}

Image::~Image()
{}

void Image::Update()
{
}

void Image::Draw()
{
	App->render->Blit(texture, pos.x - App->render->camera.x, pos.y - App->render->camera.y, &rect);
}

// Label ----------------------------------------------------------------------------

Label::Label(const char* name, iPoint pos, SDL_Texture* texture, SDL_Rect rect, p2SString text) : Element(name, LABEL, pos, texture, rect), text(text)
{}

Label::~Label()
{}

void Label::Update()
{
	// L'update si que va!
}

void Label::Draw()
{
	App->render->Blit(texture, pos.x - App->render->camera.x, pos.y - App->render->camera.y, &rect);
}

// Interactive --------------------------------------------------------------------

Interactive::Interactive(const char* name, TYPE type, iPoint pos, SDL_Texture* texture, SDL_Rect rect) : Element(name, type, pos, texture, rect)
{
	App->input->GetMousePosition(curr_mouse_pos.x, curr_mouse_pos.y);
}

Interactive::~Interactive()
{}

int Interactive::MouseState()
{
	int ret; 

	int x, y;
	App->input->GetMousePosition(x, y);
	ret = SDL_GetMouseState(&x, &y);

	return ret;
}

bool Interactive::IsOnTop()
{
	int x, y;
	App->input->GetMousePosition(x, y);

	return (x > pos.x && x < pos.x + rect.w && y > pos.y && y < pos.y + rect.h);
}

void Interactive::MoveMouse()
{
	prev_mouse_pos = curr_mouse_pos;

	App->input->GetMousePosition(curr_mouse_pos.x, curr_mouse_pos.y);

	if (curr_mouse_pos != prev_mouse_pos)
	{
		iPoint aux;
		App->input->GetMouseMotion(aux.x, aux.y);

		if (name == "scroll_but")
		{
			if (pos.y + aux.y >= 355 && pos.y + aux.y <= 500)
			{
				pos.y += aux.y;

				for (uint i = 0; i < linked_elements.Count(); i++)
				{
					if (linked_elements[i]->pos.y >= 365)
						linked_elements[i]->pos.y -= aux.y;
					else 
					{
						linked_elements[i]->rect.y += aux.y;
						linked_elements[i]->rect.h = 155;
					}
				}
			}	
		}
		else
		{
			pos += aux;

			for (uint i = 0; i < linked_elements.Count(); i++)
				linked_elements[i]->pos += aux;
		}
	}

	
}

DynamicImage::DynamicImage(const char* name, iPoint pos, SDL_Texture* texture, SDL_Rect rect) : Element(name, IMAGE, pos, texture, rect)
{
	view = false;
	key_state = IDLE;
}
DynamicImage::~DynamicImage()
{}
void DynamicImage::Update()
{
	int finalpos;
	if (App->input->GetKey(SDL_SCANCODE_UP) == true)
		key_state = UP;
	else if (App->input->GetKey(SDL_SCANCODE_DOWN) == true)
		key_state = DOWN;
	else if (App->input->GetKey(SDL_SCANCODE_LEFT) == true)
		key_state = LEFT;
	else if (App->input->GetKey(SDL_SCANCODE_RIGHT) == true)
		key_state = RIGHT;
	else
		key_state = IDLE;

}
void DynamicImage::MoveArrows()
{
	
	if (key_state == UP && pos.y > UPLIMIT)
		current_pos -= SELECTORWIDTH;
	if (key_state == DOWN && pos.y < DOWNLIMIT)
		current_pos += SELECTORWIDTH;
	if (key_state == LEFT && pos.x > LEFTLIMIT)
		current_pos--;
	if (key_state == RIGHT && pos.x < RIGHTLIMIT)
		current_pos++;

		pos = positions->GetData(current_pos);

}
void DynamicImage::Draw()
{
	if(view)
		App->render->Blit(texture, pos.x - App->render->camera.x, pos.y - App->render->camera.y, &rect);
}
void Interactive::Attach(Element* element)
{
	linked_elements.PushBack(element);
}

// Button -------------------------------------------------------------------------------

Button::Button(const char* name, iPoint pos, SDL_Texture* texture, SDL_Rect rect) : Interactive(name, BUTTON, pos, texture, rect)
{}

Button::~Button()
{}

void Button::Update()
{
	// Changing sprites depending on mouse only on button

	if (name == "button_1")
	{
		if (IsOnTop() && MouseState() == 0) rect = { 5, 115, 222, 64 };
		if (IsOnTop() && MouseState() == 1 || MouseState() == 4) rect = { 415, 170, 222, 64 };
		if (!IsOnTop()) rect = { 646, 170, 222, 64 };
	}
	
	// Moving buttons if mouse is clicked

	if (IsOnTop() && MouseState() == 1 && !App->gui->Element_Moving()) moving = true;
	if (MouseState() == 0) moving = false;


	if (moving == true) MoveMouse();
}

void Button::Draw()
{	
	App->render->Blit(texture, pos.x - App->render->camera.x, pos.y - App->render->camera.y, &rect);
}

// Text_Box -------------------------------------------------------------------------------

Text_Box::Text_Box(const char* name, iPoint pos, SDL_Texture* texture, SDL_Rect rect, p2SString text) : Interactive(name, TEXT_BOX, pos, texture, rect), text(text)
{}

Text_Box::~Text_Box()
{}

void Text_Box::Update()
{
	if (IsOnTop() && MouseState() == 1)
	{
		SDL_StartTextInput();
		editing = true;
		text = "\0";
	}

	if (!IsOnTop() && MouseState() == 1)
	{
		SDL_StopTextInput();
		editing = false;
	}

	if (editing)
	{
		text += App->input->GetString();
		texture = App->font->Print(text.GetString(), App->font->title, rect.w, rect.h);
	}
}

void Text_Box::Draw()
{
	App->render->Blit(texture, pos.x - App->render->camera.x, pos.y - App->render->camera.y, &rect);
}

// Window ----------------------------------------------------------------------------------

Window::Window(const char* name, iPoint pos, SDL_Texture* texture, SDL_Rect rect) : Interactive(name, WINDOW, pos, texture, rect)
{}

Window::~Window()
{}

void Window::Update()
{
	/*
	if (IsOnTop() && MouseState() == 1 && !App->gui->Element_Moving()) 
		moving = true;
	if (MouseState() == 0) moving = false;

	if (moving == true) Move();
	*/
}

void Window::Draw()
{
	App->render->Blit(texture, pos.x - App->render->camera.x, pos.y - App->render->camera.y, &rect);
}

