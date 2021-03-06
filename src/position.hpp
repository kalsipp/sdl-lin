#pragma once
#include <initializer_list>
#include <vector>
#include <cmath>
#include <iostream>
/*
	Class to hold x, y and z as well as perform transforms to them.
*/

class Position{
	public:
		Position();
		Position(float x, float y, float z = 0); //z is not always relevant
		Position(std::initializer_list<float>);
		void set(const Position &);
		void set(const float &, const float &, const float & z = 0);
		void rotateXZ(float);
		void rotateYZ(float);
		void rotateXY(float);
		void add(const Position & other);
		void add(const float &, const float&, const float&);
		void subtract(const Position & other);
		void subtract(const float &, const float &, const float &);
		void rotate_around(const Position & rot, const Position & origin);
		void rotate_around(float yz, float xz, float xy, const Position & origin);
		Position operator-(const Position &);
		float & x();
		float x()const;
		float & y();
		float y()const;
		float & z();
		float z()const;
		friend std::ostream & operator <<(std::ostream & stream, const Position & p);
	private:
		float m_x = 0;
		float m_y = 0;
		float m_z = 0;
		static const float to_rad;
};