#pragma once
#include <functional>
#include "collider.hpp"
class InteractionComponent{
	public:
		InteractionComponent(const Collider &);
		Collider * triggercollider();
		void reset();
		bool is_triggered();
		void trigger();
	private:
		Collider * m_triggercollider = nullptr;
		bool m_triggered = false;
};
