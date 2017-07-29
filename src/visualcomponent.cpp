#include "visualcomponent.hpp"
//#####################
Animation::Animation(){}
Animation::Animation(std::initializer_list<unsigned int> p){
	std::vector<unsigned int> anims(p);
	assert(anims.size()%2 == 0);
	for(unsigned int i = 0; i < anims.size(); i+=2){
		m_frames.push_back(std::make_pair(anims[i], anims[i+1]));
	}

}
unsigned int Animation::get_current_frame(){
	assert(m_frames.size() >= current_frame && "Attempting to get frame outsize of m_frames");

	return m_frames[current_frame].first;
}
unsigned int Animation::get_current_duration(){
	assert(m_frames.size() >= current_frame && "Attempting to get frame outsize of m_frames");
	return m_frames[current_frame].second;
}
void Animation::next_frame(){
	//std::cout << m_frames.size() << std::endl;
	current_frame++;
	if(current_frame > m_frames.size()/2) current_frame = 0;
	/*
	std::cout << "Current frame is "<< current_frame << " and the frame is " << m_frames[current_frame].first << "." << std::endl;
	std::cout << m_frames[current_frame].first << std::endl;
	*/
}
//#########################


VisualComponent::VisualComponent(){
	//m_last_animation = std::chrono::high_resolution_clock::now();
	//Animation k = {0, 300, 1, 300};
	//add_animation(0, k);

}
VisualComponent::~VisualComponent(){
	for (auto i = m_textures.begin(); i != m_textures.end(); ++i){
		delete *i;
	}
	if(m_text_texture != nullptr) delete m_text_texture;
}

void VisualComponent::add_animation(unsigned int key, const Animation& new_anim){
	m_animations[key] = new_anim;
}
void VisualComponent::set_animation(unsigned int key){
	m_current_animation = key;
}
void VisualComponent::set_centered(bool x){
	m_centered = x;
}
unsigned int VisualComponent::current_animation(){
	return m_current_animation;
}
void VisualComponent::render(SDL_Renderer* main_renderer, const Position & position){
	if(m_text_texture != nullptr) m_text_texture->render(position.x(), position.y(), main_renderer, m_centered);

	if(m_textures.size() == 0) return;	
	std::chrono::time_point<std::chrono::high_resolution_clock> now = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> diff = now-m_last_animation;
	std::chrono::milliseconds diff_ms = std::chrono::duration_cast<std::chrono::milliseconds>(diff);

	assert(m_animations.count(m_current_animation) > 0 && "The attempted animation does not exist");
	if(diff_ms.count() > m_animations[m_current_animation].get_current_duration()){
		m_last_animation = now; 
		m_animations[m_current_animation].next_frame();
	}
	//std::cout << "Current frame " << m_animations[m_current_animation].get_current_frame() << " size " << m_textures.size() << std::endl; 
	assert(m_animations[m_current_animation].get_current_frame() < m_textures.size() && "The attempted frame/texture does not exist");
	
	m_textures[m_animations[m_current_animation].get_current_frame()]->render(position.x(), position.y(), main_renderer, m_centered);

}



/*
bool VisualComponent::load_spritesheet(const std::string & path, int sprite_width, int sprite_height, SDL_Renderer * main_renderer){ 
	SDL_Surface * full_sheet = NULL;
	full_sheet = IMG_Load(path.c_str());
	if(full_sheet == NULL){
		std::cout << "Spritesheet Unable to load image " << path << " SDL Error: " << SDL_GetError() << "." << std::endl;
	}else{
		m_texture = SDL_CreateTextureFromSurface(main_renderer, full_sheet);
		if(m_texture == NULL)std::cout << "Unable to load texture SDL Error: "<< SDL_GetError() <<std::endl;
		SDL_FreeSurface(full_sheet);
	}
	SDL_Texture * k = m_texture;
	return m_texture != NULL;
}
*/
bool VisualComponent::load_text(std::string text, TTF_Font * font, SDL_Renderer * main_renderer){
	SDL_Color color = {255,255,255,255};
	SDL_Surface * textsurface = TTF_RenderText_Solid(font, text.c_str(), color);
	if(textsurface == NULL){
		std::cout << "Unable to render text surface! SDL_Ttf error: " << TTF_GetError() << std::endl;
	}else{
		
		if(m_text_texture == nullptr) m_text_texture = new Texture();
		m_text_texture->load_image_from_surface(textsurface, main_renderer);
		//m_text_texture = SDL_CreateTextureFromSurface(main_renderer, textsurface);
		SDL_FreeSurface(textsurface);
	}
	return m_text_texture != NULL;
}

bool VisualComponent::load_spritesheet(const std::string & path, int sprite_width, int sprite_height, SDL_Renderer * main_renderer){ 
	//std::cout << "Loading VS with " << path << " of size " << sprite_width << "x" << sprite_height << std::endl;
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
				//std::cout << "anotner" << std::endl; 
				SDL_Rect srcrect = {x*sprite_width, y*sprite_height, sprite_width, sprite_height};
				//std::cout << "x " << x*sprite_width << " y " << y*sprite_height << " w " << sprite_width << " h " << sprite_height << std::endl;
				
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
				
				Texture * new_text = new Texture();
				bool success = new_text->load_image_from_surface(tmp, main_renderer);
				std::string k = "Texture could not be properly loaded" + path;
				assert(success == true && k.c_str());
				m_textures.push_back(new_text);
				SDL_FreeSurface(tmp);
				pos++;

			}
		}
	}
	//SDL_FreeSurface(full_sheet);
	return success;
}
bool & VisualComponent::enabled(){
	return m_enabled;
}
void VisualComponent::scale(const int & x){
	for(unsigned int i = 0; i < m_textures.size(); ++i){
		m_textures[i]->scale(x,x);
	}
}