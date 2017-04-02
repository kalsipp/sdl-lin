#include "interactioncomponent.hpp"
#include "gameobject.hpp"
#include "mainclass.hpp"
InteractionComponent::InteractionComponent(const Collider & refcollider){
	m_triggercollider = new Collider(refcollider);
	std::cout << "Loading event"<< std::endl;
	load_event("");
	std::cout << "Done loading event" << std::endl;
}

InteractionComponent::~InteractionComponent(){
	if(m_triggercollider != nullptr) {
		delete m_triggercollider;
		m_triggercollider = nullptr;
	}
}

void InteractionComponent::load_event(const std::string & filename){
	//Load file, decrypt, for each $ make event and push in the string
	Event e("");
	m_events.push(e);
}
void InteractionComponent::start_event(Mainclass * mainclass){
	assert(m_events.size() > 0 && "in Event::start_event, Trying to start an event but no event is loaded");
	if(mainclass->start_event(m_events.front())){
		if(m_events.size() > 1){
			m_events.pop();
		}
	}
}


Collider * InteractionComponent::triggercollider(){
	return m_triggercollider;
}




void InteractionComponent::reset(){
	m_triggered = false;
}

bool InteractionComponent::triggered(){
	return m_triggered;
}

void InteractionComponent::trigger(){
	m_triggered = true;
}
