#include "action.hpp"
#include "mainclass.hpp"

Action::Action(const std::vector<std::string> & args){

}
Action::Action(){

}
Action::~Action(){

}

Action * Action::clone(){
	return new Action(*this);
}

bool Action::update(Mainclass * mainclass){
	std::cout << "Running normal action" << std::endl;
	return true;
}

//################

Action_tmp::Action_tmp(const std::vector<std::string> & args){

}

bool Action_tmp::update(Mainclass * mainclass){
	std::cout << "Running tmp action" << std::endl;
	return true;

}

Action * Action_tmp::clone(){
	return new Action_tmp(*this);
}

//###############

Action_line::Action_line(const std::vector<std::string> & args){
	m_name = args[1];
	for(unsigned int i = 2; i < args.size(); ++i){
		m_line += args[i] + " ";
	}
	m_line.pop_back();
}

bool Action_line::update(Mainclass * mainclass){
	std::cout <<m_name << ": "<< m_line << std::endl;
	return true;

}

Action * Action_line::clone(){
	return new Action_line(*this);
}