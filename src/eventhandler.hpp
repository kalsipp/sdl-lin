#pragma once
#include <vector>
#include <string>

class EventHandler{
public:

private:
	std::vector<int> decrypt(const std::string & );
	static const int EVENT_LOCK_CHARACTER;
	static const int EVENT_UNLOCK_CHARACTER;
	static const int EVENT_OPEN_CONVERSATION;
	static const int EVENT_CLOSE_CONVERSATION;
	static const int EVENT_ADD_LINE;
	static const int EVENT_SPAWN_GAMEOBJECT;
};