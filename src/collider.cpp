#include "collider.hpp"


Collider::Collider(const Position * refpos, float size_x, float size_y, bool enabled) : m_position(refpos), m_size_x(size_x), m_size_y(size_y), m_enabled(enabled){
	m_offset = Position(0,0);
}

Collider::Collider(const Position * refpos, const Position & offset, float size_x, float size_y, bool enabled): m_position(refpos), m_offset(offset), m_size_x(size_x), m_size_y(size_y), m_enabled(enabled){
}


std::pair<float, float> Collider::size(){
	return std::make_pair(size_x(), size_y());
}
std::pair<float, float> Collider::size()const{
	return std::make_pair(size_x(), size_y());
}



void Collider::set_size(float x, float y){
	m_size_x = x;
	m_size_y = y;
}

void Collider::set_is_trigger(bool val){
	m_trigger = val;
}

bool Collider::is_trigger(){
	return m_trigger;
}

void Collider::enable(bool n){
	m_enabled = n;
}
float Collider::size_x()const{
	return m_size_x*m_scale;
}
float Collider::size_y()const{
	return m_size_y*m_scale;
}
void Collider::scale(float x){
	m_scale = x;
}
float Collider::x()const{
	return m_position->x()+m_offset.x() - size_x()/2;
}

float Collider::y()const{
	return m_position->y()+m_offset.y() - size_y()/2;
}

float Collider::right()const{
	return x() + (size_x()/2);
}

float Collider::left()const{
	return x()- (size_x()/2);
}

float Collider::top()const{
	return y()+ (size_y()/2);
}

float Collider::bottom()const{
	return y() - (size_y()/2);
}

const Position & Collider::position()const{
	return *m_position;
}

void Collider::render(SDL_Renderer * main_renderer, const Position & refpos){
	int posx = round(x() - refpos.x());
	int posy = round(y()- refpos.y());
	int sizex = round(size_x());
	int sizey = round(size_y());
	SDL_Rect rekt = {posx, posy, sizex, sizey};
	SDL_RenderDrawRect(main_renderer, &rekt);  
}




bool Collider::collision_x(const Collider &other){
	if(!m_enabled) return false;
	return (abs(x() + size().first/2 - (other.x() + other.size().first/2))) * 2 < (size().first + other.size().first);
}

bool Collider::collision_y(const Collider&other){
	if(!m_enabled) return false;
	return (abs((y() + size().second/2) - (other.y() + other.size().second/2)) * 2 < (size().second + other.size().second));
}


bool Collider::collision_check(const Collider * other){
	if(!m_enabled) return false;
	if(other ==  nullptr) return false;
	return collision_x(*other) && collision_y(*other);

}