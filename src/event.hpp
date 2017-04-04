#pragma once
#include <queue>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
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
		void load_actions(const std::vector<std::string> & );
	private:
		std::vector<std::string> split_string(const std::string & instring);
		std::vector<std::string> split_by_delimiter(const std::string & in, char delimiter = ' ');
		std::queue<Action*> m_actions;
		int m_actionkey = SDLK_k;

};