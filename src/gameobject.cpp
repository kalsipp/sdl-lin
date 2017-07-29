#include "gameobject.hpp"
#include "mainclass.hpp"

Gameobject::Gameobject(Mainclass* mainclass):m_mainclass(mainclass){}
Gameobject::Gameobject(const Gameobject &){}
Gameobject::~Gameobject(){
	if(m_visualcomponent != nullptr){
		delete m_visualcomponent;
		m_visualcomponent = nullptr;
	}
	if(m_collider != nullptr){
		delete m_collider;
		m_collider = nullptr;
	}
	if(m_interactioncomponent != nullptr){
		delete m_interactioncomponent;
		m_interactioncomponent = nullptr;
	}
}

void Gameobject::update(){
}

void Gameobject::draw(){
	if(!m_enabled) return;
	if(m_visualcomponent != nullptr){
		Position p(m_position);
		if(position_world_relative)p.subtract(m_mainclass->world_position());
		m_visualcomponent->render(m_mainclass->main_renderer(), p);
	}
}

Position & Gameobject::position(){
	return m_position;
}
const Position & Gameobject::position()const{
	return m_position;
}
bool Gameobject::operator< (const Gameobject& right)const{
	std::cout << "HUT" << std::endl;
	return position().z() < right.position().z(); 
}

VisualComponent * Gameobject::visualcomponent(){
	return m_visualcomponent;
}

InteractionComponent * Gameobject::interactioncomponent(){
	return m_interactioncomponent;
}
void Gameobject::scale(float x){
	if(m_collider != nullptr){
		m_collider->scale(x/4);
	}
	if(m_visualcomponent != nullptr){
		m_visualcomponent->scale(x);
	}
	if(m_interactioncomponent != nullptr){
		m_interactioncomponent->triggercollider()->scale(x/4);
	}
}
Collider * Gameobject::collider(){
	return m_collider;
}
const std::string & Gameobject::name(){
	return m_name;
}
void Gameobject::move(float x,float y){
	m_position.x() += x;
	m_position.y() += y;
}
void Gameobject::move_to(float x,float y){
	m_position.x() = x;
	m_position.y() = y;
}

void Gameobject::set_world_relative(bool val){
	position_world_relative = val;
}
bool & Gameobject::enabled(){
	return m_enabled;
}
