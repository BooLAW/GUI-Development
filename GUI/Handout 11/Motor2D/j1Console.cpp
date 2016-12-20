#include "j1Console.h"
#include "j1Window.h"

j1Console::j1Console() 
{

}
j1Console::~j1Console()
{

}
bool j1Console::Start()
{
	console_window = (Window*)App->gui->Create_Element("console_window", WINDOW, { 0,0 }, { 0,0,768,579 });
	console_text = (Label*)App->gui->Create_Element("console_text", LABEL, { 0,0 }, {0,0,100,200});
	console_textbox = (Text_Box*)App->gui->Create_Element("console_textbox", TEXT_BOX, { 0,0 }, {0,0,300,400});
	return true;
}
bool j1Console::Update()
{
	console_window->Draw();
	console_window->
	return true;
}
bool j1Console::CleanUp()
{
	return true;
}