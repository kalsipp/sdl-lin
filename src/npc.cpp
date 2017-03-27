#include "npc.hpp"

NPC::NPC(){
	m_collider = new Collider(m_position, 96, 128);
	Collider refcollider(m_position, 128, 160);
	refcollider.set_is_trigger(true);
	m_interactioncomponent = new InteractionComponent(refcollider);
	m_visualcomponent = new VisualComponent();
	setup_animations();
}

NPC::~NPC(){
	
}

void NPC::update(Keymanager & keys, const std::vector<Gameobject*> & gameobjects){

}

void NPC::setup_animations(){

}
