#pragma once
#include <string>
#include <SDL2/SDL.h>
#include <cmath>

#include "mainclass.hpp"
#include "texture.hpp"
#include "spritesheet.hpp"
#include "position.hpp"
#include "collider.hpp"
class Mainclass;
class Spritesheet;
class Gameobject{
public:
	Gameobject(Mainclass *);
	virtual void update();
	virtual ~Gameobject();
	virtual void move(float, float);
	virtual void update_anim();
	void move_to(float, float);
	void move_to(const Position &); //Move to is a hard position set and sets oldpos = new pos
	void scale(float); 
	Position & position();
	Position position()const;
	virtual Collider * collider();
	Collider * trigger_collider();
	const int & z()const;
	float & move_speed();
	Spritesheet * spritesheet();
	void render();
	bool load_spritesheet(const std::string&);
	bool operator< (const Gameobject& right)const;
protected:
	void init_animations();
	bool anim_tick = false;
	Position m_position;
	Position m_diff_movement;
	int m_z=0;
	float m_move_speed = 3.0f;

	Collider * m_collider = NULL;
	Collider * m_trigger_collider = NULL;
	Spritesheet * m_spritesheet = NULL;
	Texture * m_texture = NULL;
	Spritesheet * m_sheet = NULL;
	Mainclass * m_mainclass = NULL;

	//Animation cycles
	/*

	*/



};