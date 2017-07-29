#include "graphicsmanager.hpp"

int GraphicsManager::m_screen_height = 768;
int GraphicsManager::m_screen_width = 1024;

bool GraphicsManager::initialize(){
	bool init_ok = true;
	if(!GraphicsManager::m_initialized){
		if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
		{
			std::cout <<  "SDL could not initialize! SDL_Error: " <<  SDL_GetError() << std::endl;
			init_ok = false;
		}
		else
		{
			if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
			{
				std::cout << "Warning: Linear texture filtering not enabled!" << std::endl;
			}
			//Create window
			m_main_window = SDL_CreateWindow( "Let's go bois", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, m_screen_width, m_screen_height, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE );
			if( m_main_window == NULL )
			{
				std::cout <<  "Window could not be created! SDL_Error:" << SDL_GetError() << std::endl;
				init_ok = false;
			}else{
				m_main_renderer = SDL_CreateRenderer(m_main_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
				m_main_surface = SDL_GetWindowSurface( m_main_window );
				if(m_main_surface == NULL){
					std::cout << "Surface could not be created! SDL Error: " << std::string(SDL_GetError()) << std::endl;
					init_ok = false;
				}
				if(m_main_renderer == NULL){
					std::cout << "Renderer could not be created! SDL Error: " << std::string(SDL_GetError()) << std::endl;
					init_ok = false;
				}else if(init_ok)
				{
					SDL_SetRenderDrawColor(m_main_renderer, 0x0, 0x0, 0x0, 0x0);
					int img_flags = IMG_INIT_PNG;
					if(!(IMG_Init(img_flags) & img_flags)){
						std::cout << "SDL_image could not initialize! SDL_image Error: " << std::string(IMG_GetError()) << std::endl;
						init_ok = false;
					}
					
					if (TTF_Init() == -1)
					{
						std::cout <<"SDL_ttf could not initialize! SDL_ttf Error: " << std::string(TTF_GetError())<<std::endl;
						init_ok = false;
					}
					
				}
			}
		}
		m_initialized = init_ok;
	}

	return init_ok;

}
void GraphicsManager::destroy(){
	SDL_DestroyRenderer(m_main_renderer);
	SDL_FreeSurface(m_main_surface);
	SDL_DestroyWindow( m_main_window );
}
SDL_Renderer * GraphicsManager::get_renderer(){
	return GraphicsManager::m_main_renderer;
}


bool GraphicsManager::m_initialized = false;
SDL_Window * GraphicsManager::m_main_window = NULL;
SDL_Surface * GraphicsManager::m_main_surface = NULL;
SDL_Renderer * GraphicsManager::m_main_renderer = NULL;