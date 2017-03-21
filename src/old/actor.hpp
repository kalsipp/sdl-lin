#pragma once
#include "gameobject.hpp"

class Gameobject;
class Actor:public Gameobject{
public:
	Actor(Mainclass *);
	virtual void update_anim();
	void dynamic_movement(const std::pair<float,float> &);
protected:
	float m_idle_anim_speed = 1000;
	float m_moving_anim_speed = 150;
	static const std::vector<int> ANIMATION_UP;
	static const std::vector<int> ANIMATION_DOWN;
	static const std::vector<int> ANIMATION_LEFT;
	static const std::vector<int> ANIMATION_RIGHT;
};