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
	m_keys[key] = val;
}

bool Keymanager::key(int key){
	if(m_keys.count(key) > 0) return m_keys.at(key);

	m_keys[key] = false;
	return false;
}