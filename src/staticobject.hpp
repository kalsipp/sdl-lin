#pragma once
#include <SDL2/SDL.h>
#include "gameobject.hpp"

class StaticObject:public Gameobject{
public:
	StaticObject();	
	virtual void draw(SDL_Renderer * );	
private:
};