#include "player.hpp"
#include "mainclass.hpp"

const int Player::ANIMATION_IDLE_UP = 0;
const int Player::ANIMATION_IDLE_DOWN = 1;
const int Player::ANIMATION_IDLE_RIGHT = 2;
const int Player::ANIMATION_IDLE_LEFT = 3;
const int Player::ANIMATION_WALKING_UP = 4;
const int Player::ANIMATION_WALKING_DOWN = 5;
const int Player::ANIMATION_WALKING_RIGHT = 6;
const int Player::ANIMATION_WALKING_LEFT = 7;


Player::Player(Mainclass * mainclass):Gameobject(mainclass){
	//m_visualcomponent.reset((new VisualComponent()));
	m_visualcomponent = new VisualComponent();
	m_collider = new Collider(&m_position, 96, 128);
	m_name = "Player";
	//m_collider.reset(new Collider());
	setup_animations();

}

Player::~Player(){
}
void Player::setup_animations(){
	{
		Animation a = {0, m_idle_anim_speed, 1, m_idle_anim_speed};
		m_visualcomponent->add_animation(ANIMATION_IDLE_UP, a);
	}
	{
		Animation a = {2, m_idle_anim_speed, 3, m_idle_anim_speed};
		m_visualcomponent->add_animation(ANIMATION_IDLE_LEFT, a);
	}
	{
		Animation a = {4, m_idle_anim_speed, 5, m_idle_anim_speed};
		m_visualcomponent->add_animation(ANIMATION_IDLE_RIGHT, a);
	}
	{
		Animation a = {6, m_idle_anim_speed, 7, m_idle_anim_speed};
		m_visualcomponent->add_animation(ANIMATION_IDLE_DOWN, a);
	}
	{
		Animation a = {0, m_walking_anim_speed, 1, m_walking_anim_speed};
		m_visualcomponent->add_animation(ANIMATION_WALKING_UP, a);
	}
	{
		Animation a = {2, m_walking_anim_speed, 3, m_walking_anim_speed};
		m_visualcomponent->add_animation(ANIMATION_WALKING_LEFT, a);
	}
	{
		Animation a = {4, m_walking_anim_speed, 5, m_walking_anim_speed};
		m_visualcomponent->add_animation(ANIMATION_WALKING_RIGHT, a);
	}
	{
		Animation a = {6, m_walking_anim_speed, 7, m_walking_anim_speed};
		m_visualcomponent->add_animation(ANIMATION_WALKING_DOWN, a);
	}
}
void Player::update(){
	update_movement();
	update_animations();
	check_event();
}

void Player::check_event(){
	if(m_mainclass->keymanager().key_down(SDLK_k)){
		for(auto i = m_mainclass->gameobjects().begin(); i != m_mainclass->gameobjects().end(); ++i){
			if((*i)->interactioncomponent() != nullptr){
				if((*i)->interactioncomponent()->triggercollider()->collision_check(collider())){
					(*i)->interactioncomponent()->trigger();
				}
			}
		}
	}
}

void Player::update_movement(){
	std::pair<float,float> player_movement = {0,0};
	//m_mainclass
	if(m_mainclass->keymanager().key(SDLK_a)) player_movement = {-m_movement_speed,0}; //m_player->move(-m_player->move_speed(),0);
	if(m_mainclass->keymanager().key(SDLK_s)) player_movement = {player_movement.first, player_movement.second + m_movement_speed};// m_player->move(0,m_player->move_speed());
	if(m_mainclass->keymanager().key(SDLK_w)) player_movement = {player_movement.first, player_movement.second - m_movement_speed};//m_player->move(0, -m_player->move_speed());
	if(m_mainclass->keymanager().key(SDLK_d)) player_movement = {player_movement.first + m_movement_speed, player_movement.second};//m_player->move(m_player->move_speed(), 0);
	//m_position.x() += player_movement.first;
	//m_position.y() += player_movement.second;
	dynamic_movement(player_movement);
}
void Player::update_animations(){


	
	if(m_diff_movement.x() == 0 && m_diff_movement.y() == 0){
		//m_spritesheet->set_anim_duration(m_idle_anim_speed);
		if(m_visualcomponent->current_animation()  == ANIMATION_WALKING_LEFT) m_visualcomponent->set_animation(ANIMATION_IDLE_LEFT);
		if(m_visualcomponent->current_animation()  == ANIMATION_WALKING_RIGHT) m_visualcomponent->set_animation(ANIMATION_IDLE_RIGHT);
		if(m_visualcomponent->current_animation()  == ANIMATION_WALKING_UP) m_visualcomponent->set_animation(ANIMATION_IDLE_UP);
		if(m_visualcomponent->current_animation()  == ANIMATION_WALKING_DOWN) m_visualcomponent->set_animation(ANIMATION_IDLE_DOWN);
		
	}else{
		if(abs(m_diff_movement.x()) >= abs(m_diff_movement.y())){ //If horizontal movement is more prevalent
			if(m_diff_movement.x() > 0){
				m_visualcomponent->set_animation(ANIMATION_WALKING_LEFT);
			}else{
				m_visualcomponent->set_animation(ANIMATION_WALKING_RIGHT);
			}
		}else{
			if(m_diff_movement.y() > 0){
				m_visualcomponent->set_animation(ANIMATION_WALKING_UP);
			}else{
				m_visualcomponent->set_animation(ANIMATION_WALKING_DOWN);
			}
		}

	}
		
}
void Player::dynamic_movement(const std::pair<float,float> & movement){
	
	//std::unique_ptr<Gameobject> mover(this);
	m_diff_movement = position();
	move(movement.first, movement.second);
	for(auto it = m_mainclass->gameobjects().begin(); it != m_mainclass->gameobjects().end(); ++it){
		if((*it) != this){
			if((*it)->collider()->collision_check(collider())){ //If we have collision
				move(-movement.first, 0); 
				if((*it)->collider()->collision_check(collider())){ //If we go back x and it's not ok
					move(movement.first, -movement.second); //We reset x and try going back y
					if((*it)->collider()->collision_check(collider())){ //If this didn't work just back both
						move(-movement.first, 0);
					}
				}
			}
		}
	}

	m_diff_movement.subtract(position());
}


/*
void Player::update_animations(Keymanager & keys){
	if(keys.key(SDLK_a)){
		m_visualcomponent->set_animation(ANIMATION_WALKING_LEFT);
	}else if(keys.key(SDLK_d)){
		m_visualcomponent->set_animation(ANIMATION_WALKING_RIGHT);
	}else if(keys.key(SDLK_w)){
		m_visualcomponent->set_animation(ANIMATION_WALKING_UP);
	}else if(keys.key(SDLK_s)){
		m_visualcomponent->set_animation(ANIMATION_WALKING_DOWN);
	}else{
		unsigned int ca = m_visualcomponent->current_animation();
		if(ca == ANIMATION_WALKING_LEFT)m_visualcomponent->set_animation(ANIMATION_IDLE_LEFT);
		if(ca == ANIMATION_WALKING_RIGHT) m_visualcomponent->set_animation(ANIMATION_IDLE_RIGHT);
		if(ca == ANIMATION_WALKING_UP) m_visualcomponent->set_animation(ANIMATION_IDLE_UP);
		if(ca == ANIMATION_WALKING_DOWN) m_visualcomponent->set_animation(ANIMATION_IDLE_DOWN);
	}
}
*/
