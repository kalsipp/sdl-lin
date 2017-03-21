#include "position.hpp"

const float Position::to_rad = M_PI/180;

Position::Position(){}

Position::Position(std::initializer_list<float> n){
	std::vector<float> p(n);
	m_x = p[0];
	m_y = p[1];
	m_z = p[2];
}

Position::Position(float x, float y, float z): m_x(x), m_y(y), m_z(z){}


void Position::set(const Position & pos){
	m_x = pos.x();
	m_y = pos.y();
	m_z = pos.z();
}
float & Position::x(){
	return m_x;
}
float Position::x()const{
	return m_x;
}
float & Position::y(){
	return m_y;
}
float Position::y()const{
	return m_y;
}
float & Position::z(){
	return m_z;
}
float Position::z()const{
	return m_z;
}
void Position::subtract(const Position & other){
	x() -= other.x();
	y() -= other.y();
	z() -= other.z();
}



void Position::rotate_around(const Position & rot, const Position & origin){
	rotate_around(rot.x(), rot.y(), rot.z(), origin);
}
void Position::rotate_around(float yz, float xz, float xy, const Position & origin){
	Position tempVector(*this);
	tempVector.subtract(origin);
	//m_start->set(origin);
	x() = origin.x();
	y() = origin.y();
	z() = origin.z();
	tempVector.rotateXY(xy);
	tempVector.rotateXZ(xz);
	tempVector.rotateYZ(yz);
	//m_start->add(tempVector);
	x() += tempVector.x();
	y() += tempVector.y();
	z() += tempVector.z();
}

void Position::rotateXY(float degrees){
	float radians = degrees*to_rad;
	float old_x = x();
	float old_y = y();
	x() = (old_x*cos(radians)) - (old_y*sin(radians));
	y() = (old_x*sin(radians)) + (old_y*cos(radians));

}

void Position::rotateXZ(float degrees){
	float radians = degrees*to_rad;
	float old_x = x();
	float old_z = z();

	x() = (old_x*cos(radians)) + (old_z*sin(radians));
	z() = -(old_x*sin(radians)) + (old_z*cos(radians));

}
void Position::rotateYZ(float degrees){
	float radians = degrees*to_rad;
	float old_y = y();
	float old_z = z();

	y() = (old_y*cos(radians)) + (old_z*sin(radians));
	z() = -(old_y*sin(radians)) + (old_z*cos(radians));

}
