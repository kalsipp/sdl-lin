#include "event.hpp"
#include "mainclass.hpp"
Event::Event(){

}

Event::Event(const std::string & filename){
	//load file
	
	Action_tmp * a = new Action_tmp();
	m_actions.push(a);
}
Event::Event(const Event & other){
	while(m_actions.size() >  0){
		delete m_actions.front();
		m_actions.pop();
	}
	std::queue<Action*> tmp = other.m_actions;
	while(tmp.size() > 0){
		Action * a = tmp.front()->clone();//new Action(*tmp.front());
		tmp.pop();
		m_actions.push(a);
	}
}
Event & Event::operator=(const Event & other){
	while(m_actions.size() >  0){
		delete m_actions.front();
		m_actions.pop();
	}
	std::queue<Action*> tmp = other.m_actions;
	while(tmp.size() > 0){
		Action * a = tmp.front()->clone();//new Action(*tmp.front());
		tmp.pop();
		m_actions.push(a);
	}
	return *this;
}
Event::~Event(){
	while(m_actions.size() > 0){
		delete m_actions.front();
		m_actions.pop();
	}

}
bool Event::update(Mainclass * mainclass){
	assert(m_actions.size() > 0 && "Event::update, attempting to run non existing action");
	bool done = m_actions.front()->update(mainclass);
	if(done){
		delete m_actions.front();
		m_actions.pop();
	}
	return m_actions.size() != 0;
}
