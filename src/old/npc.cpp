#include "npc.hpp"
#include "mainclass.hpp"

NPC::NPC(Mainclass * mainclass):Gameobject(mainclass){
	m_trigger_collider = new Collider(m_position, 128,128);
}