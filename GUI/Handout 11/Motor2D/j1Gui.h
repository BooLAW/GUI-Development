#ifndef __j1GUI_H__
#define __j1GUI_H__

#include "j1Module.h"
#include "j1App.h"
#include "j1Render.h"
#include "j1Fonts.h"

#define CURSOR_WIDTH 2

#define UPLIMIT 100
#define DOWNLIMIT 150
#define LEFTLIMIT 250
#define RIGHTLIMIT 430

#define SELECTORWIDTH 4




enum TYPE
{
	IMAGE,
	LABEL,
	BUTTON,
	TEXT_BOX,
	WINDOW,
	DYNAMICIMAGE,
	SELECTOR
};
enum keypressed
{
	IDLE,
	UP,
	DOWN,
	LEFT,
	RIGHT
};

// TODO 1: Create your structure of classes

class Element
{
public:

	Element(const char* name, TYPE type, iPoint pos, SDL_Texture* texture, SDL_Rect rect);
	virtual ~Element();

	virtual void Update() {}
	virtual void Draw() {}
	virtual void Handle_Input() {}

public:

	const char* name;
	iPoint pos;
	SDL_Rect rect;
	TYPE type;
	SDL_Texture* texture;

	// ????
	bool moving = false;

};

// ------------------------------------------------------------------

class Image : public Element
{
public:

	Image(const char* name, iPoint pos, SDL_Texture* texture, SDL_Rect rect);
	~Image();

	void Update();
	void Draw();
public:
	bool active;
};

// ------------------------------------------------------------------

class Label : public Element
{
public:

	Label(const char* name, iPoint pos, SDL_Texture* texture, SDL_Rect rect, p2SString text);
	~Label();

	void Update();
	void Draw();

private:

	p2SString text;
};

// ------------------------------------------------------------------

class Interactive : public Element
{
public:

	Interactive(const char* name, TYPE type, iPoint pos, SDL_Texture* texture, SDL_Rect rect);
	virtual ~Interactive();

	int MouseState();
	bool IsOnTop();
	void MoveMouse();

	void Attach(Element* element);

protected:

	uint tab_id = 0;
	p2DynArray<Element*> linked_elements;

private:
	// ?????
	iPoint curr_mouse_pos;
	iPoint prev_mouse_pos;
};

// ------------------------------------------------------------------
class DynamicImage : public Element
{
public:

	DynamicImage(const char* name, iPoint pos, SDL_Texture* texture, SDL_Rect rect);
	~DynamicImage();

	void Update();
	void Draw();
	void MoveArrows();
public:
	keypressed key_state;
	bool view;
	p2DynArray <iPoint> positions[8];
	int current_pos;

};
class Text_Box : public Interactive
{
public:

	Text_Box(const char* name, iPoint pos, SDL_Texture* texture, SDL_Rect rect, p2SString text);
	~Text_Box();

	void Update();
	void Draw();
	void Handle_Input() {}

private:

	p2SString text;
	uint cursor = 0;
	bool editing;
};

// ----------------------------------------------------------------------

class Button : public Interactive
{
public: 
	Button(const char* name, iPoint pos, SDL_Texture* texture, SDL_Rect rect);
	~Button();

	void Update();
	void Draw();
	void Handle_Input() {}
};

// ----------------------------------------------------------------------

class Window : public Interactive
{
public:

	Window(const char* name, iPoint pos, SDL_Texture* texture, SDL_Rect rect);
	~Window();

	void Update();
	void Draw();
	void Handle_Input() {}
};

// ======================================================================

class j1Gui : public j1Module
{
public:
	j1Gui();
	virtual ~j1Gui();

	bool Awake(pugi::xml_node&);  
	bool Start();	              
	bool PreUpdate();             
	bool PostUpdate();            
	bool CleanUp();               

	const SDL_Texture* GetAtlas() const;

	// TODO 2: Create the factory methods
	Element* Create_Element(const char* name, TYPE type, iPoint pos, SDL_Rect rect, p2SString text = nullptr, _TTF_Font* font = NULL);
	void Destroy_Element(const char* name);

	bool Element_Moving();

private:

	p2DynArray<Element*> elements;
	uint curr_id = 0;
	SDL_Texture* atlas;
	p2SString atlas_file_name;
};

#endif // __j1GUI_H__