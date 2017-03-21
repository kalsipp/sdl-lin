#pragma once


#include "actor.hpp"
class Actor;
//class Mainclass;
class Player:public Actor{
public:
	Player(Mainclass *);
	virtual void update();

private:

	


};