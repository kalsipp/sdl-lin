#include "event.hpp"
#include "mainclass.hpp"
Event::Event(){
}

Event::Event(const std::string & actions){

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
void Event::load_actions(const std::vector<std::string> & actions){


	for(unsigned int i = 0; i < actions.size(); ++i){
		std::vector<std::string> line = split_by_delimiter(actions[i]);
		
		if(line[0] == "line"){
			Action_line * a = new Action_line(line);
			m_actions.push(a);

		}else if(line[0] == "hure"){

		}

	}
}

std::vector<std::string> Event::split_by_delimiter(const std::string & in, char delimiter){
	std::vector<std::string> out; 
	std::string in_work;

	for(unsigned int i = 0; i < in.size(); ++i){
		if(in[i] != delimiter){
		in_work.push_back(in[i]);
		}else{
			out.push_back(in_work);
			in_work = "";
		}
	}
	out.push_back(in_work);
	return out;
}

bool Event::update(Mainclass * mainclass){ //False = done
	if(m_actions.size() <= 0) return false;
	//assert(m_actions.size() > 0 && "Event::update, attempting to run non existing action");
	bool done = m_actions.front()->update(mainclass);
	if(done){
		delete m_actions.front();
		m_actions.pop();
	}
	return m_actions.size() != 0;
}
