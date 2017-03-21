#pragma once
#include <initializer_list>
#include <vector>
#include <cmath>

/*
	Class to hold x, y and z as well as perform transforms to them.
*/

class Position{
	public:
		Position();
		Position(std::initializer_list<float>);
		Position(float x, float y, float z = 0); //z is not always relevant
		void set(const Position &);
		void rotateXZ(float);
		void rotateYZ(float);
		void rotateXY(float);
		void subtract(const Position & other);
		void add(float x = 0, float y = 0, float z = 0);
		void rotate_around(const Position & rot, const Position & origin);
		void rotate_around(float yz, float xz, float xy, const Position & origin);
		float & x();
		float x()const;
		float & y();
		float y()const;
		float & z();
		float z()const;
	private:
		float m_x = 0;
		float m_y = 0;
		float m_z = 0;
		static const float to_rad;
};