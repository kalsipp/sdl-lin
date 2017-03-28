#include "interactioncomponent.hpp"

const unsigned int InteractionComponent::TRIGGER_USE = 0;

InteractionComponent::InteractionComponent(const Collider & refcollider){
	m_triggercollider = new Collider(refcollider);
}

Collider * InteractionComponent::triggercollider(){
	return m_triggercollider;
}

void InteractionComponent::set_triggercondition(unsigned int i){
	m_triggercondition = i;
}
unsigned int InteractionComponent::triggercondition(){
	return m_triggercondition;
}


void InteractionComponent::reset(){
	m_triggerlist.clear();
}

std::vector<Gameobject*> InteractionComponent::triggered(){
	std::vector<Gameobject*> k = m_triggerlist;
	m_triggerlist.clear();
	return k;
}

void InteractionComponent::trigger(Gameobject * triggles){
	m_triggerlist.push_back(triggles);
}
