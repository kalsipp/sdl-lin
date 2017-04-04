#pragma once
#include <string>
#include <vector>
class Mainclass;
class Action{
public:
	Action();
	Action(const std::vector<std::string> &);
	virtual ~Action();
	virtual bool update(Mainclass * mainclass);
	virtual Action * clone();
private:
};

class Action_tmp: public Action{
public:
	Action_tmp(const std::vector<std::string> &);
	Action_tmp(){};
	virtual ~Action_tmp(){}
	virtual bool update(Mainclass*);
	virtual Action * clone();
private:
};

class Action_line: public Action{
public:
	Action_line(const std::vector<std::string> &);
	Action_line(){};
	virtual ~Action_line(){}
	virtual bool update(Mainclass*);
	virtual Action * clone();
private:
	std::string m_line; 
	std::string m_name;
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

