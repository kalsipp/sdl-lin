/*
#pragma once
#include <SDL2/SDL.h>
#include <memory>

class Component{
public:
	virtual Component();
	virtual ~Component();
	virtual void update();
private:
	
};
class VisualComponent:public Component{
public:
	VisualComponent(); 
	void load_spritesheet();
	void draw();
private:
};


class Gameobject{
	Gameobject(){}
	virtual update(){
		foreach component in components{
			component.update();
		}
	}
	virtual late_update(){
		visuals->draw();
	}

	std::vector<Component> components; 
};




int main(){
	Gameobject olle;

	for each gameobject{
		gameobject.update();
	}
	for each gameobject{
		gameobject.draw();
	}
}
*/