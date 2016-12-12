#pragma once
#ifndef _UI_IMAGE_
#define _UI_IMAGE_

#include "UI_Element.h"
#include "j1Render.h"
#include "j1Gui.h"
#include "j1App.h"

class UI_Image : public UI_Element {
public:
	UI_Image(TYPE _type, iPoint _pos, SDL_Rect _rect, SDL_Texture* _texture) :UI_Element(_type, _pos, _rect, _texture)
	{
	};
	void InnerDraw()
	{
		App->render->Blit(App->gui->GetAtlas(), pos.x, pos.y, &image_rect);
	};
	bool Update();
public:
	SDL_Rect image_rect;
};
#endif // !_UI_Image_
