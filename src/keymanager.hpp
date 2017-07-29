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
	void set_mouse(bool);
	bool mouse();
	bool mouse_down();
	void text_input(const std::string &);
	void reset_text();
	std::string get_text();
private:
	std::map<int,bool> m_keys;
	std::map<int,bool> m_keys_down;
	bool m_mouse_state = false;
	bool m_mouse_down = false;
	std::string m_textinput;
};