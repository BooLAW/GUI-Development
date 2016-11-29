#ifndef __j1GUI_H__
#define __j1GUI_H__

#include "j1Module.h"
#include "p2SString.h"
#include "p2DynArray.h"
#define CURSOR_WIDTH 2

enum TYPE{BACKGROUND,BUTTON,TEXTBOX};
// TODO 1: Create your structure of classes
class UI_Element
{
public:
	SDL_Rect rect;
	uint id;
	enum TYPE;
protected:	
	virtual void Update() {};
	virtual void Draw() {};
	virtual void Handle_Input() {};
};

class Texture : public UI_Element
{
	SDL_Texture* tex;
};

class Interactive_element : public UI_Element
{
public:
	bool highlighted;
	bool clicked;
	uint tab_id;
public:
	bool IsClicked() ;
	bool IsOnTop() ;
};

class Background : public Texture
{
private:
	void Update() {};
	void Draw() 
	{
		SDL_blit();
	};
};

class Button : public Texture, Interactive_element
{
private:
	void Draw() {};
	void Update() {};
	void Handle_Input() {};
};
class Label : public Texture, Interactive_element
{
	p2SString text;
	uint bar_pos;

private:
	void Draw() {};
	void Update() {};
	void Handle_Input() {};

		
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
	const SDL_Texture* GetAtlas() const;
	p2DynArray<UI_Element*> elements;
private:

	SDL_Texture* atlas;
	p2SString atlas_file_name;

};

#endif // __j1GUI_H__