#pragma once 
#include <vector>
#include <cassert>
#include <map>
#include <chrono>
#include "position.hpp"
#include "texture.hpp"
#include "component.hpp"


struct Animation{
public:
	Animation();
	Animation(std::initializer_list<unsigned int>);
	//const std::vector<std::pair<unsigned int,unsigned int>> & frames()const;
	unsigned int get_current_frame();
	unsigned int get_current_duration();
	void next_frame();
private:
	unsigned int current_frame = 0;
	std::vector<std::pair<unsigned int,unsigned int>> m_frames;
};


class VisualComponent{
public:
	VisualComponent();
	~VisualComponent();
	void add_animation(unsigned int, const Animation&);
	void set_animation(unsigned int);
	unsigned int current_animation();
	void render(SDL_Renderer * , const Position &);
	bool & enabled();
	bool load_spritesheet(const std::string & path, int sprite_width, int sprite_height, SDL_Renderer * main_renderer);
	void scale(const int & x);
private:
	bool m_enabled = false;
	unsigned int m_current_animation = 0;
	unsigned int m_current_frame = 0;
	std::chrono::time_point<std::chrono::high_resolution_clock> m_last_animation;
	std::map<int, Animation> m_animations;
	std::vector<Texture*> m_textures;
	SDL_Texture * m_texture = NULL;
	
};