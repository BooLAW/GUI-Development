#pragma once
#ifndef _UI_LABEL_
#define _UI_LABEL_
#include"UI_Element.h"
class UI_Element;
class UI_Label : public  UI_Element
{
public:
	_TTF_Font* text_font;
	p2SString text;
	uint bar_pos;
public:
	UI_Label(TYPE _type, iPoint _pos, SDL_Rect _rect, SDL_Texture* _texture, uint _tab_id, bool _active, char* _text, _TTF_Font* _text_font) : UI_Interactive_element(_type, _pos, _rect, _texture, _tab_id, _active)
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
	void Draw();
	bool Update();
	void Handle_Input();
};

#endif // !_UI_LABEL_
