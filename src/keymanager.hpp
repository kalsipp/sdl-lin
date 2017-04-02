#pragma once
#include <map>
#include <SDL2/SDL.h>
#include <iostream>

class Keymanager{
public:
	Keymanager();
	bool key(int); //If key currently down 
	bool key_down(int); //If key went down this tick
	void set(int, bool);
	void update();
private:
	std::map<int,bool> m_keys;
	std::map<int,bool> m_keys_down;
};