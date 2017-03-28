#pragma once
#include <utility>
#include <cstddef>
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "position.hpp"

/*
	Box collider
*/

class Gameobject;

class Collider{
public:
	Collider(const Position * refpos, float sizex, float sizey, bool enabled = true); 
	Collider(const Position * refpos, const Position & offset, float sizex, float sizey, bool enabled = true);
	std::pair<float,float> size();	
	std::pair<float,float> size()const;
	void set_size(float x, float y);
	void set_is_trigger(bool);
	bool is_trigger();
	Gameobject * parent();
	bool collision_x(const Collider &);
	bool collision_y(const Collider &);
	bool collision_check(const Collider *); //Checks collision in x and y. z is ignored. 
	const Position & position()const;
	float x();
	float x()const;
	float y();
	float y()const;
	float right()const;
	float left()const;
	float top()const;
	float bottom()const;
	void render(SDL_Renderer * main_renderer);
private:
	Gameobject * m_parent = nullptr;
	const Position * m_position; //points to parent's position. 
	Position m_offset;
	bool m_trigger = false;
	float m_size_x = 32;
	float m_size_y = 32;
	bool m_enabled = false;
};