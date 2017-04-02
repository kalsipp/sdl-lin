#include "action.hpp"
#include "mainclass.hpp"

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

bool Action_tmp::update(Mainclass * mainclass){
	std::cout << "Running tmp action" << std::endl;
	return true;

}

Action * Action_tmp::clone(){
	return new Action_tmp(*this);
}