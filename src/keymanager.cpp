#include "keymanager.hpp"

Keymanager::Keymanager(){
	m_keys[SDLK_a] = false;
	m_keys[SDLK_w] = false;
	m_keys[SDLK_s] = false;
	m_keys[SDLK_d] = false;
	m_keys[SDLK_RIGHT] = false;
	m_keys[SDLK_LEFT] = false;
	m_keys[SDLK_UP] = false;
	m_keys[SDLK_DOWN] = false;
	m_keys[SDLK_p] = false;
	m_keys[SDLK_m] = false;
}

void Keymanager::set(int key, bool val){

	if(m_keys.count(key) == 0){ 
		m_keys[key] = false;
		//std::cout <<"keys " << m_keys[key] << " val " << val << std::endl;
	}
	if(m_keys[key] == true && val == false) { //key just went up
		m_keys_down[key] = false;
	}else if(m_keys[key] == false && val == true){ //key just went down
		
		m_keys_down[key] = true;
	}else{
		m_keys_down[key] = false;
	}
	m_keys[key] = val;
}

bool Keymanager::key_down(int key){
	if(m_keys_down.count(key) > 0) {
		return m_keys_down.at(key);
	}
	m_keys_down[key] = false;
	return false;
}
void Keymanager::set_mouse(bool val){
	if(m_mouse_state != val){
		m_mouse_down = val;
	}
	m_mouse_state = val;
}

bool Keymanager::mouse(){
	return m_mouse_state;
}
bool Keymanager::mouse_down(){
	return m_mouse_down;
}

void Keymanager::update(){
	for(auto i = m_keys.begin(); i != m_keys.end(); ++i){
		m_keys_down[i->first] = false;
	}
	m_mouse_down = false;
}

bool Keymanager::key(int key){
	if(m_keys.count(key) > 0) return m_keys.at(key);

	m_keys[key] = false;
	return false;
}
void Keymanager::text_input(const std::string & text){
	m_textinput += text;
}
std::string Keymanager::get_text(){
	return m_textinput;
}
void Keymanager::reset_text(){
	m_textinput = "";
}