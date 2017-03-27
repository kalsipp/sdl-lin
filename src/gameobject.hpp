#pragma once
#include <SDL2/SDL.h>
#include <map>
#include <memory>
#include <vector>
#include "visualcomponent.hpp"
#include "collider.hpp"
#include "keymanager.hpp"
#include "interactioncomponent.hpp"
//#include <SDL2/SDL_image.h>
//#include <SDL2/SDL_ttf.h>


#include "position.hpp"

class Gameobject{
public:
	Gameobject();
	Gameobject(const Gameobject &);
	virtual ~Gameobject();
	virtual void update(Keymanager &, const std::vector<Gameobject*> & gameobjects);
	virtual void draw(SDL_Renderer *);
	Position & position();
	const Position & position()const;
	virtual void move(float,float);
	virtual void move_to(float,float);
	bool operator<(const Gameobject  &)const;
	VisualComponent* visualcomponent();
	InteractionComponent * interactioncomponent();
	Collider* collider();
	//const Collider & collider()const;
protected:
	Position m_position;

	VisualComponent * m_visualcomponent = nullptr;
	Collider * m_collider = nullptr;
	InteractionComponent * m_interactioncomponent = nullptr;

};