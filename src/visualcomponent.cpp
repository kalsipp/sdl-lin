#include "visualcomponent.hpp"

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



VisualComponent::VisualComponent(){
	//Animation k = {0, 300, 1, 300};
	//add_animation(0, k);

}
VisualComponent::~VisualComponent(){
	for (auto i = m_textures.begin(); i != m_textures.end(); ++i){
		delete *i;
	}
}

void VisualComponent::add_animation(unsigned int key, const Animation& new_anim){
	m_animations[key] = new_anim;
}
void VisualComponent::set_animation(unsigned int key){
	m_current_animation = key;
}
unsigned int VisualComponent::current_animation(){
	return m_current_animation;
}
void VisualComponent::render(SDL_Renderer* main_renderer, const Position & position){

	std::chrono::time_point<std::chrono::high_resolution_clock> now = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> diff = now-m_last_animation;
	std::chrono::milliseconds diff_ms = std::chrono::duration_cast<std::chrono::milliseconds>(diff);

	assert(m_animations.count(m_current_animation) > 0 && "The attempted animation does not exist");
	if(diff_ms.count() > m_animations[m_current_animation].get_current_duration()){
		m_last_animation = now; 
		m_animations[m_current_animation].next_frame();
	}
	assert(m_animations[m_current_animation].get_current_frame() < m_textures.size() && "The attempted frame/texture does not exist");
	m_textures[m_animations[m_current_animation].get_current_frame()]->render(position.x(), position.y(), main_renderer);
}



bool VisualComponent::load_spritesheet(const std::string & path, int sprite_width, int sprite_height, SDL_Renderer * main_renderer){ 
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
				Texture * new_text = new Texture();
				//Texture * new_text = new Texture();
				new_text->load_image_from_surface(tmp, main_renderer);
				m_textures.push_back(new_text);
				pos++;

			}
		}
	}
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