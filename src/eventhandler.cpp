#include "eventhandler.hpp"

const int EventHandler::EVENT_LOCK_CHARACTER = 0;
const int EventHandler::EVENT_UNLOCK_CHARACTER = 1;
const int EventHandler::EVENT_OPEN_CONVERSATION = 2;
const int EventHandler::EVENT_CLOSE_CONVERSATION = 3;
const int EventHandler::EVENT_ADD_LINE = 4;
const int EventHandler::EVENT_SPAWN_GAMEOBJECT = 5;

std::vector<int> EventHandler::decrypt(const std::string & filename){
	std::vector<int> k = {1,2};
	return k;
}