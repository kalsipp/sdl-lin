#include "gameobject.hpp"

Gameobject::Gameobject(){}
Gameobject::Gameobject(const Gameobject &){}
Gameobject::~Gameobject(){
	if(m_visualcomponent != nullptr) delete m_visualcomponent;
	if(m_collider != nullptr) delete m_collider;
	if(m_interactioncomponent != nullptr) delete m_interactioncomponent;

}

void Gameobject::update(Keymanager & keys, const std::vector<Gameobject*> & gameobjects){
}

void Gameobject::draw(SDL_Renderer * main_renderer){
	if(m_visualcomponent != nullptr){
		m_visualcomponent->render(main_renderer, m_position);
	}
}

Position & Gameobject::position(){
	return m_position;
}
const Position & Gameobject::position()const{
	return m_position;
}
bool Gameobject::operator< (const Gameobject& right)const{
	return position().z() < right.position().z(); 
}

VisualComponent * Gameobject::visualcomponent(){
	return m_visualcomponent;
}

InteractionComponent * Gameobject::interactioncomponent(){
	return m_interactioncomponent;
}

Collider * Gameobject::collider(){
	return m_collider;
}

void Gameobject::move(float x,float y){
	m_position.x() += x;
	m_position.y() += y;
}
void Gameobject::move_to(float x,float y){
	m_position.x() = x;
	m_position.y() = y;
}


/*
Collider & Gameobject::collider(){
	return *m_collider;
}
const Collider & Gameobject::collider()const{
	return *m_collider;
}
*/