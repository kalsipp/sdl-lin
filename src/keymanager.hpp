#pragma once
#include <map>
#include <SDL2/SDL.h>

class Keymanager{
public:
	Keymanager();
	bool key(int);
	void set(int, bool);
private:
	std::map<int,bool> m_keys;
};