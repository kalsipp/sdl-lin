#pragma once
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

class GraphicsManager{
	public:
		static bool initialize();
		static void destroy();
		static SDL_Renderer * get_renderer();
		static void render();
	private:
		GraphicsManager(){}
		static int m_screen_height;
		static int m_screen_width;
		static bool m_initialized;
		static SDL_Window * m_main_window;
		static SDL_Surface * m_main_surface;
		static SDL_Renderer * m_main_renderer;
};