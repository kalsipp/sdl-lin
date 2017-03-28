#include "npc.hpp"

const int NPC::ANIMATION_IDLE_UP = 0;
const int NPC::ANIMATION_IDLE_DOWN = 1;
const int NPC::ANIMATION_IDLE_RIGHT = 2;
const int NPC::ANIMATION_IDLE_LEFT = 3;
const int NPC::ANIMATION_WALKING_UP = 4;
const int NPC::ANIMATION_WALKING_DOWN = 5;
const int NPC::ANIMATION_WALKING_RIGHT = 6;
const int NPC::ANIMATION_WALKING_LEFT = 7;


NPC::NPC(){
	m_collider = new Collider(&m_position, 96, 128);
	Collider refcollider(&m_position, 128, 160);
	refcollider.set_is_trigger(true);
	m_interactioncomponent = new InteractionComponent(refcollider);
	m_visualcomponent = new VisualComponent();
}

NPC::~NPC(){
	
}

void NPC::update(Keymanager & keys, const std::vector<Gameobject*> & gameobjects){
	std::vector<Gameobject*> triggerlist = m_interactioncomponent->triggered();
	while(triggerlist.size() != 0){
		Gameobject * triggles = triggerlist.back();
		triggerlist.pop_back();
		triggered(triggles);
	}
}

void NPC::triggered(Gameobject* triggles){
	std::cout << triggles->name() << std::endl;
}


void NPC::setup_animations(){
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
	m_visualcomponent->set_animation(ANIMATION_IDLE_DOWN);
}

void NPC::setup_animations(const std::vector<Animation> & anims){
	for(unsigned int i = 0; i < anims.size(); ++i){
		m_visualcomponent->add_animation(i, anims[i]);
	}
}