#pragma once
#include "gameobject.hpp"
#include "interactioncomponent.hpp"
#include "visualcomponent.hpp"
class NPC:public Gameobject{
	public:
		NPC();
		~NPC();
		virtual void update(Keymanager &, const std::vector<Gameobject*> & gameobjects);
	private:
		void setup_animations();
		void triggered(Gameobject *);
};