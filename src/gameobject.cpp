#include "gameobject.hpp"

Gameobject::Gameobject(){}
Gameobject::Gameobject(const Gameobject &){}
Gameobject::~Gameobject(){}

void Gameobject::update(Keymanager & keys, const std::vector<std::unique_ptr<Gameobject>> & gameobjects){
}

void Gameobject::draw(SDL_Renderer * ){}

Position & Gameobject::position(){
	return m_position;
}
const Position & Gameobject::position()const{
	return m_position;
}
bool Gameobject::operator< (const Gameobject& right)const{
	return position().z() < right.position().z(); 
}

VisualComponent & Gameobject::visualcomponent(){
	return *m_visualcomponent;
}