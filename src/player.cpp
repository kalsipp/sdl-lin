#include "player.hpp"


const int Player::ANIMATION_IDLE_UP = 0;
const int Player::ANIMATION_IDLE_DOWN = 1;
const int Player::ANIMATION_IDLE_RIGHT = 2;
const int Player::ANIMATION_IDLE_LEFT = 3;
const int Player::ANIMATION_WALKING_UP = 4;
const int Player::ANIMATION_WALKING_DOWN = 5;
const int Player::ANIMATION_WALKING_RIGHT = 6;
const int Player::ANIMATION_WALKING_LEFT = 7;


Player::Player(){
	m_visualcomponent.reset((new VisualComponent()));
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
void Player::update(Keymanager & keys, const std::vector<std::unique_ptr<Gameobject>> & gameobjects){
	update_movement(keys);
	update_animations(keys);
}

void Player::update_movement(Keymanager & keys){
	std::pair<float,float> player_movement = {0,0};
	//m_mainclass
	if(keys.key(SDLK_a)) player_movement = {-m_movement_speed,0}; //m_player->move(-m_player->move_speed(),0);
	if(keys.key(SDLK_s)) player_movement = {player_movement.first, player_movement.second + m_movement_speed};// m_player->move(0,m_player->move_speed());
	if(keys.key(SDLK_w)) player_movement = {player_movement.first, player_movement.second - m_movement_speed};//m_player->move(0, -m_player->move_speed());
	if(keys.key(SDLK_d)) player_movement = {player_movement.first + m_movement_speed, player_movement.second};//m_player->move(m_player->move_speed(), 0);
	m_position.x() += player_movement.first;
	m_position.y() += player_movement.second;
}

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

void Player::draw(SDL_Renderer* main_renderer){
	m_visualcomponent->render(main_renderer, m_position);
}