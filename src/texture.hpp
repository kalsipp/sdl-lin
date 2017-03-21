#pragma once
#include <string>
#include <iostream>
#include <cmath>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>


/*
	Wrapping class around an SDL_texture. 
*/

class Texture{
public:
	Texture();
	~Texture();
	Texture(const Texture &);
	void render(float x, float y, SDL_Renderer *, SDL_RendererFlip flip = SDL_FLIP_NONE);
	void scale(float x, float y);
	bool load_image_from_surface(SDL_Surface *, SDL_Renderer *);
	bool load_image_from_file(const std::string & path, SDL_Renderer*);
private:
	float m_scale_x = 1;
	float m_scale_y = 1;
	SDL_Texture * m_my_texture = NULL;
	SDL_Surface * m_my_surface = NULL;
	//pointer to the game's main renderer. Get's casted non-const when passed to SDL functions.
	std::string m_source_path;
};