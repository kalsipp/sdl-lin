#include "actor.hpp"
#include "mainclass.hpp"

//#include "gameobject.hpp"

const std::vector<int> Actor::ANIMATION_UP = {0, 1};
const std::vector<int> Actor::ANIMATION_DOWN = {6, 7};
const std::vector<int> Actor::ANIMATION_LEFT = {4,5};
const std::vector<int> Actor::ANIMATION_RIGHT ={2, 3} ;


Actor::Actor(Mainclass * mainclass):Gameobject(mainclass){
	m_spritesheet = new Spritesheet(mainclass->main_renderer());
	/*
	m_spritesheet->set_anim_duration(m_idle_anim_speed);
	m_spritesheet->set_pattern(ANIMATION_DOWN);
	*/
}


void Actor::update_anim(){
	if(m_diff_movement.x() == 0 && m_diff_movement.y() == 0){
		m_spritesheet->set_anim_duration(m_idle_anim_speed);
	}else{
		m_spritesheet->set_anim_duration(m_moving_anim_speed);
		if(abs(m_diff_movement.x()) >= abs(m_diff_movement.y())){ //If horizontal movement is more prevalent
			if(m_diff_movement.x() > 0){
				m_spritesheet->set_pattern(ANIMATION_RIGHT);
			}else{
				m_spritesheet->set_pattern(ANIMATION_LEFT);
			}
		}else{
			if(m_diff_movement.y() > 0){
				m_spritesheet->set_pattern(ANIMATION_UP);
			}else{
				m_spritesheet->set_pattern(ANIMATION_DOWN);
			}
		}

	}
}

void Actor::dynamic_movement(const std::pair<float,float> & movement){
	Actor * mover = this;
	m_diff_movement = mover->position();
	mover->move(movement.first, movement.second);
	for(auto it = m_mainclass->gameobjects().begin(); it != m_mainclass->gameobjects().end(); ++it){
		if((*it) != mover){
			if((*it)->collider()->collision_check(mover->collider())){ //If we have collision
				mover->move(-movement.first, 0); 
				if((*it)->collider()->collision_check(mover->collider())){ //If we go back x and it's not ok
					mover->move(movement.first, -movement.second); //We reset x and try going back y
					if((*it)->collider()->collision_check(mover->collider())){ //If this didn't work just back both
						mover->move(-movement.first, 0);
					}
				}
			}
		}
	}

	m_diff_movement.subtract(mover->position());
}