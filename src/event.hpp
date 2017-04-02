#pragma once
#include <queue>
#include <string>
#include <SDL2/SDL.h>
#include "action.hpp"
class Mainclass;
class Event{
	public:
		Event();
		Event(const Event &);
		~Event();
		Event & operator=(const Event & );
		Event(const std::string & filename);
		bool update(Mainclass * mainclass);
	private:
		std::queue<Action*> m_actions;
		int m_actionkey = SDLK_k;

};