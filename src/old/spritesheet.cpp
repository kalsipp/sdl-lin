#include "spritesheet.hpp"


Spritesheet::Spritesheet(const SDL_Renderer * main_renderer): m_main_renderer(main_renderer){
	//m_main_renderer = main_renderer;

}

Spritesheet::~Spritesheet(){
	for(unsigned int i = 0; i < m_textures.size(); ++i){
		delete m_textures[i];
	}
}





void Spritesheet::scale(const int & x){
	for(unsigned int i = 0; i < m_textures.size(); ++i){
		m_textures[i]->scale(x,x);
	}
}

bool Spritesheet::load_from_file(const std::string & path, int sprite_width, int sprite_height){ 
	SDL_Surface * full_sheet = NULL;
	full_sheet = IMG_Load(path.c_str());
	bool success = true;
	if(full_sheet == NULL){
		std::cout << "Spritesheet Unable to load image " << path << " SDL Error: " << SDL_GetError() << "." << std::endl;
		success = false;
	}else{
		assert(full_sheet->w%sprite_width == 0 && full_sheet->h%sprite_height==0);
		int y_max = round(full_sheet->h/sprite_height);
		int x_max = round(full_sheet->w/sprite_width);
		int pos = 0;
		for(int y = 0; y < y_max; ++y){
			for(int x = 0; x < x_max; ++x){
				SDL_Rect srcrect = {x*sprite_width, y*sprite_height, sprite_width, sprite_height};
				SDL_Surface * tmp = SDL_CreateRGBSurface(
					full_sheet->flags, 
					sprite_width, 
					sprite_height,
					32, 
					full_sheet->format->Rmask, 
					full_sheet->format->Gmask, 
					full_sheet->format->Bmask, 
					full_sheet->format->Amask
					);
				SDL_BlitSurface(full_sheet, &srcrect, tmp, NULL); 
				Texture * new_text = new Texture(m_main_renderer);
				new_text->load_image_from_surface(tmp);
				m_textures.push_back(new_text);
				pos++;

			}
		}
	}
	return success;
}

void Spritesheet::set_anim_duration(const int & n){
	m_anim_duration = n;
}

void Spritesheet::set_pattern(const std::vector<int> & nv){
	if(m_pattern != nv){
		m_pattern = nv;
		m_current_anim = 0;
	}
}

void Spritesheet::update_anim(){
	std::chrono::time_point<std::chrono::high_resolution_clock> now = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> diff = now-m_last_anim;
	std::chrono::milliseconds diff_ms = std::chrono::duration_cast<std::chrono::milliseconds>(diff);

	if(diff_ms.count() > m_anim_duration){
		m_last_anim = now;
		++m_current_anim;
		if(m_current_anim >= m_pattern.size()) m_current_anim = 0;
	}
	
}

Texture * Spritesheet::get_next_anim(){;
	if(m_textures.size() == 0) std::cout << "Warning m_textures size is 0" << std::endl;
	return m_textures[m_pattern[m_current_anim]];
}

Texture * Spritesheet::get_text(const int & n){
	//if(n > size()*size()-1){
	//	std::cout << "Warning out of bounds in spritesheet: " << n << std::endl;
	//}
	return m_textures[n];
}