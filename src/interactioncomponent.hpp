#pragma once
#include <functional>
#include "collider.hpp"
class Gameobject;
class InteractionComponent{
	public:
		InteractionComponent(const Collider &);
		Collider * triggercollider();
		void set_triggercondition(unsigned int);
		unsigned int triggercondition();
		void reset();
		std::vector<Gameobject*> triggered();
		void trigger(Gameobject *);
	private:
		Collider * m_triggercollider = nullptr;
		Gameobject * m_triggerer = nullptr;
		std::vector<Gameobject*> m_triggerlist;
		bool m_triggered = false;
		static const unsigned int TRIGGER_USE;
		unsigned int m_triggercondition = 0; 
};
