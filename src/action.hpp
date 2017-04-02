#pragma once

class Mainclass;
class Action{
public:
	 Action();
	virtual ~Action();
	virtual bool update(Mainclass * mainclass);
	virtual Action * clone();
private:
};

class Action_tmp: public Action{
public:
	Action_tmp(){};
	virtual ~Action_tmp(){}
	virtual bool update(Mainclass*);
	virtual Action * clone();
private:
};

/*
$ 	
lock player
open conversation
setface media/happyface.png
line dude Hello world
setface media/angryface.png
line dude this makes me upset
giveitem 42
linegiveitem 42
close conversation
unlock player
*/

