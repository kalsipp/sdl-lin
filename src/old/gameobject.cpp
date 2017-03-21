#include "gameobject.hpp"

/*

const std::vector<int> Gameobject::ANIMATION_WALKING_UP = {0,1,2,3};
const std::vector<int> Gameobject::ANIMATION_WALKING_DOWN = {4,5,6,7};
const std::vector<int> Gameobject::ANIMATION_WALKING_LEFT = {12,13,14,15};
const std::vector<int> Gameobject::ANIMATION_WALKING_RIGHT = {8,9,10,11};
*/


Gameobject::Gameobject(Mainclass * mainclass):m_mainclass(mainclass){
	//m_main_renderer = main_renderer;
	//m_spritesheet = new Spritesheet(mainclass->main_renderer());
	//m_old_position = new Position();
	m_collider = new Collider(m_position, 96, 96);
	//m_spritesheet->set_pattern(ANIMATION_IDLE_DOWN); //Default anim is idle down. 
	//m_spritesheet->set_anim_duration(m_idle_anim_speed);
}

Gameobject::~Gameobject(){
	if(m_spritesheet != NULL){
		delete m_spritesheet;
		m_spritesheet = NULL; 
	}
	
	if(m_collider != NULL){
		delete m_collider;
		m_collider = NULL;
	}
}

bool Gameobject::operator< (const Gameobject& right)const{
	return position().z() < right.position().z(); 
}

void Gameobject::scale(float x){
	if(m_spritesheet != NULL){
		m_spritesheet->scale(x);
	}
}

void Gameobject::update(){

}

void Gameobject::move(float nx, float ny){
	position().x()+=nx;
	position().y()+=ny;
}



void Gameobject::move_to(float nx, float ny){
	position().x() = nx;
	position().y() = ny;
}

void Gameobject::move_to(const Position & pos){
	position().set(pos);
}

Position & Gameobject::position(){
	return m_position;
}
Position Gameobject::position()const{
	return m_position;
}

Collider * Gameobject::collider(){
	return m_collider;
}

Collider * Gameobject::trigger_collider(){
	return m_trigger_collider;
}

void Gameobject::update_anim(){
	
}

float & Gameobject::move_speed(){
	return m_move_speed;
}
Spritesheet * Gameobject::spritesheet(){
	return m_spritesheet;
}

void Gameobject::render(){	
	if(m_spritesheet != NULL){
		m_spritesheet->update_anim();
		m_spritesheet->get_next_anim()->render(position().x(), position().y());
	}else{
		m_texture->render(position().x(), position().y());
	}
}


bool Gameobject::load_spritesheet(const std::string & path){
	if(m_spritesheet == NULL) m_spritesheet = new Spritesheet(m_mainclass->main_renderer());
		if(m_spritesheet->load_from_file(path, 32, 32)){
			m_spritesheet->set_anim_duration(300);
			return true;
		}
	return false;
}
