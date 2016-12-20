#ifndef __j1SCENE_H__
#define __j1SCENE_H__

#include "j1Module.h"

struct SDL_Texture;

class Image;
class Label;
class Text_Box;
class Button;
class Window;
class DynamicImage;

class j1Scene : public j1Module
{
public:

	j1Scene();

	// Destructor
	virtual ~j1Scene();

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

	SDL_Texture* debug_tex;

	Label* Player_select;

	DynamicImage* P1_Sel;
	DynamicImage* P2_Sel;

	Image* Background;

	Image* Blanka1;
	Image* Ryu1;
	Image* Ken1;
	Image* Honda1;
	Image* Guile1;
	Image* Chunli1;
	Image* Zangief1;
	Image* Dhalism1;

	Image* Blanka2;
	Image* Ryu2;
	Image* Ken2;
	Image* Honda2;
	Image* Guile2;
	Image* Chunli2;
	Image* Zangief2;
	Image* Dhalism2;


	Label* but1_text;

	Label* description;

	Image* box_name;
	Text_Box* type_name;

	iPoint face_honda;
	iPoint face_ryu;
	iPoint face_ken;
	iPoint face_blanka;
	iPoint face_guile;
	iPoint face_chunli;
	iPoint face_zangief;
	iPoint face_dhalism;

	bool p1=true;
public:
	
};

#endif // __j1SCENE_H__