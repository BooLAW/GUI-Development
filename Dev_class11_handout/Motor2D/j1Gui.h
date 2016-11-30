#ifndef __j1GUI_H__
#define __j1GUI_H__

#include "j1Module.h"
#include "p2SString.h"
#include "p2DynArray.h"
#include "j1Fonts.h"
#define CURSOR_WIDTH 2

enum TYPE{BACKGROUND,BUTTON,LABEL,WINDOW};
// TODO 1: Create your structure of classes
class UI_Element
{
public:
	SDL_Rect rect;
	uint id;
	TYPE type;
	iPoint pos;
	SDL_Texture* texture;
	bool debug_mode;
	UI_Element* parent;
	p2List<UI_Element*> linked_elements;
public: 
	UI_Element(TYPE _type, iPoint _pos, SDL_Rect _rect, SDL_Texture* _texture) :type(_type), pos(_pos), rect(_rect), texture(_texture) {
	};
	virtual void Update() ;
	virtual void Draw() ;
	virtual void Handle_Input() ;
};


class Interactive_element : public UI_Element
{
public:
	bool hovering;
	bool r_clicked;
	bool l_clicked;
	uint tab_id;
	bool moving;
public:
	Interactive_element() {};
	void Handle_Input();
	bool RightClicked() ;
	bool LeftClicked();
	bool IsOnTop() ;
};

class Window : public Interactive_element
{
public:
	void Set(SDL_Rect _rect, SDL_Texture* _IdleTex)
	{
		rect.x = _rect.x;
		rect.y = _rect.y;
		rect.w = _rect.w;
		rect.y = _rect.h;
		texture = _IdleTex;
	}
	void Update() ;
	void Draw() ;
	void Handle_Input() ;
};

class Button : public  Interactive_element
{
private:
	void Set(SDL_Rect _rect,SDL_Texture* _IdleTex) 
	{
		rect.x = _rect.x;
		rect.y = _rect.y;
		rect.w = _rect.w;
		rect.y = _rect.h;
		texture = _IdleTex;
	}
	void Draw() ;
	void Update() ;
	void Handle_Input() ;
};
class Label : public  Interactive_element
{
public:
	_TTF_Font* text_font;
	p2SString text;
	uint bar_pos;
public:
	void Set(SDL_Rect _rect, _TTF_Font* _font)
	{
		rect.x = _rect.x;
		rect.y = _rect.y;
		rect.w = _rect.w;
		rect.y = _rect.h;
		text_font = _font;
	}
	void Change_Text(p2SString _text)
	{
		char* tmp = new char[_text.Length() + 1];
		strcpy_s(tmp, _text.Length() + 1, _text.GetString());
		text = tmp;
	}
private:
	void Draw() ;
	void Update() ;
	void Handle_Input() ;

		
};
// ---------------------------------------------------
class j1Gui : public j1Module
{
public:

	j1Gui();

	// Destructor
	virtual ~j1Gui();

	// Called when before render is available
	bool Awake(pugi::xml_node&);

	// Call before first frame
	bool Start();

	// Called before all Updates
	bool PreUpdate();

	// Called after all Updates
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();

	// TODO 2: Create the factory methods
	UI_Element* Create_Element(TYPE mytype);
	UI_Element* Destroy_Element(uint id);

	// Gui creation functions
	SDL_Texture* GetAtlas() const;
	p2DynArray<UI_Element*> elements;
private:

	SDL_Texture* atlas;
	SDL_Texture* background;
	
	p2SString atlas_file_name;
	p2SString background_file_name;

};

#endif // __j1GUI_H__