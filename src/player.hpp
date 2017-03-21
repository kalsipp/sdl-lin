#pragma once
#include <SDL2/SDL.h>
#include <memory>
#include "gameobject.hpp"
#include "visualcomponent.hpp"
#include "keymanager.hpp"
class Player:public Gameobject{
	public:
		Player();
		~Player();
		virtual void update(Keymanager & keys, const std::vector<std::unique_ptr<Gameobject>> & gameobjects);
		virtual void draw(SDL_Renderer *);
	private:
		void setup_animations();
		void update_animations(Keymanager & keys);
		void update_movement(Keymanager & keys);
		static const int ANIMATION_IDLE_UP;
		static const int ANIMATION_IDLE_DOWN;
		static const int ANIMATION_IDLE_RIGHT;
		static const int ANIMATION_IDLE_LEFT;
		static const int ANIMATION_WALKING_UP;
		static const int ANIMATION_WALKING_DOWN;
		static const int ANIMATION_WALKING_RIGHT;
		static const int ANIMATION_WALKING_LEFT;
		float m_movement_speed = 1;
		unsigned int m_walking_anim_speed = 200;
		unsigned int m_idle_anim_speed = 1000;

};