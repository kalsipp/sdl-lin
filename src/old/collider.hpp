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

class Collider{
public:
	Collider(const Position & refpos, float sizex, float sizey, bool enabled = true); 
	Collider(const Position & refpos, Position & offset, float sizex, float sizey, bool enabled = true);
	std::pair<float,float> size();	
	std::pair<float,float> size()const;
	void set_size(float x, float y);
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
	const Position & m_position; //points to parent's position. 
	Position m_offset;
	float m_size_x;
	float m_size_y;
	bool m_enabled;
};