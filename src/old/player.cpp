#include "player.hpp"
#include "mainclass.hpp"

//#include "actor.hpp"
Player::Player(Mainclass * mainclass):Actor(mainclass){
	m_trigger_collider = new Collider(m_position, 128, 128);
}

void Player::update(){
	std::pair<float,float> player_movement = {0,0};
	//m_mainclass
	if(m_mainclass == NULL) std::cout << "Mainclass null" << std::endl;
	m_mainclass->key(SDLK_a);
	if(m_mainclass->key(SDLK_a)) player_movement = {-move_speed(),0}; //m_player->move(-m_player->move_speed(),0);
	if(m_mainclass->key(SDLK_s)) player_movement = {player_movement.first, player_movement.second + move_speed()};// m_player->move(0,m_player->move_speed());
	if(m_mainclass->key(SDLK_w)) player_movement = {player_movement.first, player_movement.second - move_speed()};//m_player->move(0, -m_player->move_speed());
	if(m_mainclass->key(SDLK_d)) player_movement = {player_movement.first + move_speed(), player_movement.second};//m_player->move(m_player->move_speed(), 0);
	dynamic_movement(player_movement);



	for(unsigned int i = 0; i < m_mainclass->gameobjects().size(); ++i){
		m_mainclass->gameobjects()[i]->collider()->collision_check(collider());
	}

	update_anim();
	/*
	*/
}

