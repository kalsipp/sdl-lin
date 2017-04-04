#pragma once
#include <string>
#include <queue>
#include "event.hpp"
#include "collider.hpp"
class Gameobject;
class Mainclass;
class InteractionComponent{
	public:
		InteractionComponent(const Collider &);
		~InteractionComponent();
		Collider * triggercollider();
		void load_event(const std::string & filename);
		void start_event(Mainclass *);
		void reset();
		bool triggered();
		void trigger();
	private:
		std::string decrypt(const std::string & instring);
		Collider * m_triggercollider = nullptr;
		bool m_triggered = false;
		std::queue<Event> m_events;
};
