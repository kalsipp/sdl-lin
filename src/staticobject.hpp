#pragma once
#include <SDL2/SDL.h>
#include "gameobject.hpp"

class StaticObject:public Gameobject{
public:
	StaticObject(Mainclass * );	
	virtual ~StaticObject(){}
private:
};