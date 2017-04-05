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











/*
 x
<->
XXX XXX ^ 
X X X X |y  	x + sizex/2 = right edge.  
XXX XXX v   	x - sizex/2 = left edge. 
				y + sizey/2 = top edge. 
				y - sizey/2 = bot edge.

if(my right edge is more than your left and your left is not less than my left)



return (abs(x() - other.x()) * 2 < (size().first + other.size().first)) &&
         (abs(y() - other.y()) * 2 < (size().second + other.size().second));
*/

bool Collider::collision_x(const Collider &other){
	if(!m_enabled) return false;
	return (abs(x() + size().first/2 - (other.x() + other.size().first/2))) * 2 < (size().first + other.size().first);
}

bool Collider::collision_y(const Collider&other){
	if(!m_enabled) return false;
	return (abs((y() + size().second/2) - (other.y() + other.size().second/2)) * 2 < (size().second + other.size().second));
}

/*
*/
bool Collider::collision_check(const Collider * other){
	if(!m_enabled) return false;
	if(other ==  nullptr) return false;
	//std::cout << "HUr" << std::endl;
	
	//if() std::cout  << "horizontally" << std::endl;
	//if() std::cout << "vertically" << std::endl;
	//if(!(left() < other.right() || right() > other.left())) std::cout  << "horizontally" << std::endl;
	//if(!(top() < other.bottom() || bottom() > other.top())) std::cout << "vertically" << std::endl;
	return collision_x(*other) && collision_y(*other);
	//return (abs(x() + size().first/2 - (other.x() + other.size().first/2))) * 2 <= (size().first + other.size().first) 
	//&& (abs((y() + size().second/2) - (other.y() + other.size().second/2)) * 2 <= (size().second + other.size().second));


	//return (abs(x() - other.x()) * 2 < (size().first + other.size().first)) &&
         //(abs(y() - other.y()) * 2 < (size().second + other.size().second));
	
/*
	std::cout << "hut" << std::endl;
	if(right() > other.left() && other.left() > left()){
	//if((right() > other.left() && right() < other.right() )|| (left() < other.right() && left() > other.left())){
		std::cout << "Collider is horizontally colliding" << std::endl;
		if(top() > other.bottom() && top() < other.top()){
			std::cout << "Collider is vertically colliding" << std::endl;
			return true;
		}
	}
	return false;
	*/
}