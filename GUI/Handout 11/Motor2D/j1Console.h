#pragma once
#ifndef J1_CONSOLE
#define J1_CONSOLE

#include "j1Module.h"
#include "j1Gui.h"
class Window;
class Text_Box;
class Label;
class j1Console : public j1Module
{
public:
	j1Console();

	virtual ~j1Console();
	// Called before render is available

	bool Start();
	//bool Awake(pugi::xml_node&);
	// Called each loop iteration
	bool Update();
	// Called before quitting
	bool CleanUp();
public:
	Window* console_window = nullptr;
	Text_Box* console_textbox = nullptr;
	Label* console_text = nullptr;
	
};
#endif // !J1_CONSOLE
