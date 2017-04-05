#pragma once
#include <SDL2/SDL.h>
#include <map>
#include <memory>
#include <vector>
#include "visualcomponent.hpp"
#include "collider.hpp"
#include "keymanager.hpp"
#include "interactioncomponent.hpp"
#include "position.hpp"


class Mainclass;
class Gameobject{
public:
	Gameobject(Mainclass*);
	Gameobject(const Gameobject &);
	virtual ~Gameobject();
	virtual void update();
	virtual void draw();
	Position & position();
	const Position & position()const;
	virtual void move(float,float);
	virtual void move_to(float,float);
	virtual void setup_animations(){}
	virtual void scale(float x);
	const std::string & name();
	virtual void setup_animations(const std::vector<Animation> &){}
	virtual void triggered(Gameobject *){}
	bool operator<(const Gameobject  &)const;
	VisualComponent* visualcomponent();
	InteractionComponent * interactioncomponent();
	Collider* collider();
	//const Collider & collider()const;
protected:
	Mainclass * m_mainclass = nullptr;
	Position m_position;
	std::string m_name = "";
	VisualComponent * m_visualcomponent = nullptr;
	Collider * m_collider = nullptr;
	InteractionComponent * m_interactioncomponent = nullptr;

};