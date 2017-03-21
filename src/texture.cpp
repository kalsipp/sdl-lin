#include "texture.hpp"


Texture::Texture(){
	//m_main_renderer = renderer;

}



Texture::~Texture(){
	SDL_FreeSurface(m_my_surface);
	SDL_DestroyTexture(m_my_texture);
}

bool Texture::load_image_from_surface(SDL_Surface * new_surf, SDL_Renderer * main_renderer){
	m_my_surface = new_surf;
	m_my_texture = SDL_CreateTextureFromSurface(main_renderer, new_surf);
	return m_my_texture != NULL;
}
bool Texture::load_image_from_file(const std::string & path, SDL_Renderer * main_renderer){
	m_source_path = path; 
	if(m_my_texture != NULL) {
		SDL_DestroyTexture(m_my_texture);
		m_my_texture = NULL;
	}
	std::cout << "Loading image " << m_source_path << "." << std::endl;
	m_my_surface = IMG_Load(m_source_path.c_str());
	if(m_my_surface == NULL){
		std::cout << "Unable to load image " << m_source_path << " SDL Error: " << SDL_GetError() << "." << std::endl;
	}else{
		std::cout << "Image is " <<  std::to_string(m_my_surface->w) << "w, " << std::to_string(m_my_surface ->h) << "h." << std::endl;
		//SDL_Renderer * rend = const_cast<SDL_Renderer*>(main_renderer);
		m_my_texture = SDL_CreateTextureFromSurface(main_renderer, m_my_surface);
		if(m_my_texture == NULL){
			std::cout << "Unable to create texture from " << m_source_path << "! SDL Error: " << SDL_GetError() << ".";
		}
	}

	return m_my_texture != NULL;
}

void Texture::scale(float x, float y){
	//std::cout << "Scaling texture to x:" << x << " y:" << y << std::endl;
	m_scale_x = x;
	m_scale_y = y;
}



void Texture::render(float x, float y, SDL_Renderer * main_renderer , SDL_RendererFlip fliptype){

	//std::cout << "x " << x << " y " << y << " width " << m_my_surface->w << " height " << m_my_surface->h << std::endl;


	int scalex = m_my_surface->w*m_scale_x;
	int scaley = m_my_surface->h*m_scale_y;
	int posx = round(x);
	int posy = round(y);
	SDL_Rect scalerect = {posx,posy,scalex, scaley};
	//SDL_RenderCopy(m_main_renderer, m_my_texture, clip, &renderquad);
	//SDL_Renderer * rend = const_cast<SDL_Renderer*>(m_main_renderer);
	SDL_RenderCopyEx(main_renderer, m_my_texture, NULL, &scalerect, 0, NULL, fliptype);
}