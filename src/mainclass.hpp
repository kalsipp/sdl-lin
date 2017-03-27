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
	~Mainclass();
	void run();
	//const std::vector<std::unique_ptr<Gameobject>> & gameobjects()const;
	//bool key(int);
	//const SDL_Renderer * main_renderer()const;

private:	
	void setup_keys(); //Allocate m_keys and set values
	void setup_gameobjects(); //Generate gameobjects for the current map
	void update_keys();
	float m_frame_delay = 1/60;
	std::chrono::time_point<std::chrono::high_resolution_clock> m_last_frame;

	//void dyn_movement(Gameobject *, const std::pair<float, float> &);
	SDL_Window * m_main_window = NULL;
	SDL_Surface * m_main_surface = NULL;
	SDL_Renderer * m_main_renderer = NULL;
	int m_screen_height = 640;
	int m_screen_width = 480;
	bool m_init_ok = true;
	bool m_running = true; //Set false to shut down main game loop. 
	SDL_Event m_main_event; //Event container
	Keymanager keymanager;
	//sstd::map<int, bool> m_keys; //<sdl's macro for a key, it's current value>
	std::vector<Gameobject*> m_gameobjects;
	//Player * m_player; //Note that player also exists in m_gameobjects
	bool debug_show_colliders = false;
};