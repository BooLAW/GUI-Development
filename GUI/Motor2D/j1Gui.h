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
	iPoint pos;
	SDL_Texture* texture;
	uint id;
	TYPE type;
	UI_Element* parent;
	bool debug_mode;
public: 
	UI_Element(TYPE _type, iPoint _pos, SDL_Rect _rect, SDL_Texture* _texture) :type(_type), pos(_pos), rect(_rect), texture(_texture)
	{
	};
	virtual ~UI_Element();

	virtual void Update() ;
	virtual void Draw() ;
	virtual void Handle_Input() ;

	//functional functions
	void SetPos(int x, int y);
	iPoint GetPos()const;

	void SetRect(SDL_Rect _rect);

	void SetParent(UI_Element* _parent);
};

//--------INTERACTIVE ELEMENTS-------
class UI_Interactive_element : public UI_Element
{
public:
	bool hovering;
	bool r_clicked;
	bool l_clicked;
	bool moving;
	bool active;
	uint tab_id;
	
public:
	UI_Interactive_element(TYPE _type, iPoint _pos, SDL_Rect _rect, SDL_Texture* _texture,uint _tab_id,bool _active) :UI_Element(_type,_pos,_rect,_texture)
	{
		active = _active;
		hovering = r_clicked = l_clicked = moving = false;
		tab_id = _tab_id;
	};
	virtual ~UI_Interactive_element();
	void Handle_Input();
	bool RightClicked() ;
	bool LeftClicked();
	bool IsOnTop() ;
};

class UI_Window : public UI_Interactive_element
{
public:
	
public:
	UI_Window(TYPE _type, iPoint _pos, SDL_Rect _rect, SDL_Texture* _texture, uint _tab_id, bool _active) :UI_Interactive_element(_type, _pos, _rect, _texture, _tab_id,_active)
	{
	}
	virtual ~UI_Window();
	void Update() ;
	void Draw() ;
	void Handle_Input() ;
};

class UI_Button : public  UI_Interactive_element
{
public:
	UI_Button(TYPE _type, iPoint _pos, SDL_Rect _rect, SDL_Texture* _texture, uint _tab_id, bool _active) :UI_Interactive_element(_type,_pos,_rect,_texture,_tab_id,_active)
	{
	};
	virtual ~UI_Button();
	void Draw() ;
	void Update() ;
	void Handle_Input() ;
};
class UI_Label : public  UI_Interactive_element
{
public:
	_TTF_Font* text_font;
	p2SString text;
	uint bar_pos;
public:
	UI_Label(TYPE _type, iPoint _pos, SDL_Rect _rect, SDL_Texture* _texture, uint _tab_id, bool _active,char* _text, _TTF_Font* _text_font) : UI_Interactive_element(_type, _pos, _rect, _texture, _tab_id, _active)
	{
		text_font = _text_font;
		text.create(_text);
		texture = App->font->Print(text.GetString());
		bar_pos = 0;
	};
	virtual ~UI_Label();
	void Change_Text(p2SString _text)
	{
		if (texture != NULL)
			SDL_DestroyTexture(texture);

		texture = App->font->Print(_text.GetString());
	}
public:
	void Draw() ;
	void Update() ;
	void Handle_Input() ;	
};

class UI_TextBox : public UI_Label {
public:
	uint bar_pos;
	uint max_char;
public:
	UI_TextBox();
	virtual ~UI_TextBox();
	void Draw();
	void Update();
	void Handle_Input();
};
//--------------UNACTIVE ELEMENTS----------------------

class UI_Background : public UI_Element {
public:
	UI_Background(TYPE _type, iPoint _pos, SDL_Rect _rect, SDL_Texture* _texture) :UI_Element(_type, _pos, _rect, _texture) 
	{
	};
	void Draw();
	void Update();
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

	// Factory methods
	UI_Element* Create_Element(TYPE _type, iPoint _pos, SDL_Rect _rect, SDL_Texture* _texture, uint _tab_id, bool _active, char* _text, _TTF_Font* _text_font);

	SDL_Texture* GetAtlas() const;
	SDL_Texture* GetBackground() const;
	p2List<UI_Element*> elements;
private:

	SDL_Texture* atlas;
	SDL_Texture* background;
	
	p2SString atlas_file_name;
	p2SString background_file_name;

};
#endif // __j1GUI_H__