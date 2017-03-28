#pragma once
#include "gameobject.hpp"
#include "interactioncomponent.hpp"
#include "visualcomponent.hpp"
class NPC:public Gameobject{
	public:
		NPC();
		~NPC();
		virtual void update(Keymanager &, const std::vector<Gameobject*> & gameobjects);
		virtual void setup_animations();
		virtual void setup_animations(const std::vector<Animation> &);
	protected:
		virtual void triggered(Gameobject *);
		unsigned int m_walking_anim_speed = 200;
		unsigned int m_idle_anim_speed = 1000;

		

		static const int ANIMATION_IDLE_UP;
		static const int ANIMATION_IDLE_DOWN;
		static const int ANIMATION_IDLE_RIGHT;
		static const int ANIMATION_IDLE_LEFT;
		static const int ANIMATION_WALKING_UP;
		static const int ANIMATION_WALKING_DOWN;
		static const int ANIMATION_WALKING_RIGHT;
		static const int ANIMATION_WALKING_LEFT;
};