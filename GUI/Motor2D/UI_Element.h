#pragma once
#ifndef _UI_ELEMENT_
#define _UI_ELEMENT_

#include "j1App.h"
#include "j1Module.h"
#include "p2SString.h"
#include "p2DynArray.h"
#include "j1Fonts.h"
#include "j1Render.h"
#include "SDL\include\SDL.h"


enum TYPE { BACKGROUND, BUTTON, LABEL, WINDOW };

class UI_Element
{
public:
	SDL_Rect rect;
	iPoint pos;
	SDL_Texture* texture;
	uint id;
	p2List<j1Module*> listeners;
	bool debug_mode;
private:
	UI_Element* parent;
	TYPE type;
public:
	UI_Element(TYPE _type, iPoint _pos, SDL_Rect _rect, SDL_Texture* _texture) :type(_type), pos(_pos), rect(_rect), texture(_texture)
	{
	};
	virtual ~UI_Element();

	virtual bool Update() 
	{
		return true;
	}
	virtual void Draw()
	{
		
	}
	virtual void Handle_Input();

	//functional functions
	void UI_Element::SetPos(int x, int y)
	{
		pos.x = x;
		pos.y = y;
	}
	void UI_Element::SetRect(SDL_Rect _rect)
	{
		rect = _rect;
	}
	void UI_Element::SetParent(UI_Element* _parent)
	{
		parent = _parent;
	}
	iPoint GetPos()const
	{
		if (parent != nullptr)
		{
			//the position is set respect the parent, so:
			return iPoint(pos.x + parent->pos.x, pos.y + parent->pos.y);
		}
		else
		{
			return iPoint(pos.x, pos.y);
		}
	}
};
#endif // !_UI_ELEMENT_


