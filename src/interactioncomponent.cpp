#include "interactioncomponent.hpp"

InteractionComponent::InteractionComponent(const Collider & refcollider){
	m_triggercollider = new Collider(refcollider);
}

Collider * InteractionComponent::triggercollider(){
	return m_triggercollider;
}
void InteractionComponent::reset(){
	m_triggered = false;
}
bool InteractionComponent::is_triggered(){
	return m_triggered;
}
void InteractionComponent::trigger(){
	m_triggered = true;
}
