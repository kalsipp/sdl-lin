#pragma once
#include <SDL2/SDL.h>
#include <memory>
#include "gameobject.hpp"
#include "visualcomponent.hpp"
#include "keymanager.hpp"
#include "collider.hpp"
class Player:public Gameobject{
	public:
		Player(Mainclass *);
		~Player();
		virtual void update();
		virtual void setup_animations();
	protected:
		void update_animations();
		void dynamic_movement(const std::pair<float,float> & movement);
		void update_movement();
		void check_event();
		static const int ANIMATION_IDLE_UP;
		static const int ANIMATION_IDLE_DOWN;
		static const int ANIMATION_IDLE_RIGHT;
		static const int ANIMATION_IDLE_LEFT;
		static const int ANIMATION_WALKING_UP;
		static const int ANIMATION_WALKING_DOWN;
		static const int ANIMATION_WALKING_RIGHT;
		static const int ANIMATION_WALKING_LEFT;
		float m_movement_speed = 1;
		Position m_diff_movement;
		unsigned int m_walking_anim_speed = 200;
		unsigned int m_idle_anim_speed = 1000;

};