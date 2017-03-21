#pragma once
#include <SDL2/SDL.h>
#include <map>
#include <memory>
#include <vector>
#include "visualcomponent.hpp"
#include "collider.hpp"
#include "keymanager.hpp"
//#include <SDL2/SDL_image.h>
//#include <SDL2/SDL_ttf.h>


#include "position.hpp"

class Gameobject{
public:
	Gameobject();
	Gameobject(const Gameobject &);
	virtual ~Gameobject();
	virtual void update(Keymanager &, const std::vector<std::unique_ptr<Gameobject>> & gameobjects);
	virtual void draw(SDL_Renderer *);
	Position & position();
	const Position & position()const;
	bool operator<(const Gameobject  &)const;
	VisualComponent & visualcomponent();
protected:
	Position m_position;
	std::unique_ptr<VisualComponent> m_visualcomponent = nullptr;
	std::unique_ptr<Collider> m_collider = nullptr;

};