#include "interactioncomponent.hpp"
#include "gameobject.hpp"
#include "mainclass.hpp"
InteractionComponent::InteractionComponent(const Collider & refcollider){
	m_triggercollider = new Collider(refcollider);
	//load_event("scripts/script.scr");
}

InteractionComponent::~InteractionComponent(){
	if(m_triggercollider != nullptr) {
		delete m_triggercollider;
		m_triggercollider = nullptr;
	}
}

void InteractionComponent::load_event(const std::string & filename){
	//Load file, decrypt, for each $ make event and push in the string
	std::ifstream infile(filename.c_str());
	std::string data;
	std::stringstream buffer;
	buffer << infile.rdbuf();
	infile.close();
	data = buffer.str();
	data = decrypt(data);
	std::istringstream iss(data);
	std::string line;
	Event in_work;
	std::vector<std::string> actions; 
	
	while(std::getline(iss, line)){
		if(line[0] == '#'){
			//Do nothing lmao
		}else if(line[0] == '$'){ //New event, save old, make new
			in_work.load_actions(actions);
			m_events.push(in_work);
			actions.clear();
			in_work = Event();
		}else{
			actions.push_back(line);
		}
	}
	
	Event e;
	e.load_actions(actions);
	m_events.push(e);
	//std::cout << "I have " << m_events.size() << " events" << std::endl;
}

std::string InteractionComponent::decrypt(const std::string & in){
	char key = 'p';
	std::string n = in;
	for(unsigned int i = 0; i < in.size(); ++i){
		n[i] = key^in[i];
	}
	return n;
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
