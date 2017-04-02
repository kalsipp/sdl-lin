#include "staticobject.hpp"

StaticObject::StaticObject(Mainclass * mainclass) : Gameobject(mainclass){
	m_visualcomponent = new VisualComponent();
	/*
	*/
	m_collider = new Collider(&m_position, 32, 32,  true);
	Animation a = {0, 10000};
	m_visualcomponent->add_animation(0,a);
}


