#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <map>
#include <utility>
#include <vector>
#include <algorithm>
#include <memory>
#include <time.h>
#include "gameobject.hpp"
#include "staticobject.hpp"
#include "player.hpp"
#include "keymanager.hpp"
#include "npc.hpp"
#include "collider.hpp"
/*
#include "texture.hpp"

#include "spritesheet.hpp"
*/
/*
	This class contains 
	The main game loop, deals with key inputs, gameobject generation and initialization. 
	Also updates player and triggers all gameobjects updates. 
*/
//class Gameobject;

class Mainclass{
public: 
	Mainclass();
	virtual ~Mainclass();
	void run();
	std::vector<Gameobject*> & gameobjects();
	Keymanager & keymanager();
	SDL_Renderer * main_renderer();
	Gameobject * player();
	const Position & world_position();
	bool start_event(const Event &); //return true if event started.


protected:	
	std::vector<std::string> split_by_delimiter(const std::string & in, char delimiter);
	std::string trim(const std::string& str, const std::string& whitespace = " \t");
	void setup_gameobjects(); //Generate gameobjects for the current map
	void update_keys();
	void post_update();
	void render();
	float m_frame_delay = 1/60;
	std::chrono::time_point<std::chrono::high_resolution_clock> m_last_frame;

	SDL_Window * m_main_window = NULL;
	SDL_Surface * m_main_surface = NULL;
	SDL_Renderer * m_main_renderer = NULL;
	Player * m_player = nullptr;
	Position m_world_position;
	int m_screen_height = 640;
	int m_screen_width = 480;
	bool m_init_ok = true;
	bool m_running = true; //Set false to shut down main game loop. 
	SDL_Event m_main_event; //Event container
	Keymanager m_keymanager;
	std::vector<Gameobject*> m_gameobjects;
	bool debug_show_colliders = false;
	Event m_current_event;
	bool m_event_ongoing = false;
};