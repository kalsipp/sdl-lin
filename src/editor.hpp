
#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <map>
#include <utility>
#include <vector>
#include <algorithm>
#include <memory>
#include <time.h>
#include "gameobject.hpp"
#include "staticobject.hpp"
#include "player.hpp"
#include "keymanager.hpp"
#include "npc.hpp"
#include "mainclass.hpp"
class Editor: public Mainclass{
public:
	Editor();
	virtual ~Editor();
	void editor_run();

private:	
	TTF_Font * m_font;
	Gameobject * m_mouse_object = nullptr;
	Position m_mouse_position;
	Collider * m_mouse_collider = nullptr;
};
