#ifndef VECTOR2D_H
#define VECTOR2D_H

#include<math.h>

class Vector2D
{
public:
	Vector2D(float x, float y): m_x(x), m_y(y) {}		//standard constructor

	float getX() { return m_x; }				//classic java style getters
	float getY() { return m_y; }

	void setX(float x) { m_x = x; }			//and setters
	void setY(float y) { m_y = y; }

	float length() { return sqrt(m_x * m_x + m_y * m_y); }

	//okay we are about to get into som crazy stuff but im too tired for this rn
	//soo ill leave it with this for now
	//
	Vector2D operator+(const Vector2D& v2) const{
		return Vector2D(m_x + v2.m_x, m_y + v2.m_y);
	}
	friend Vector2D& operator+=(Vector2D& v1, const Vector2D& v2){		//this has to be a friend because its accessing private variables of another class definition!
		v1.m_x += v2.m_x;
		v1.m_y += v2.m_y;
		return v1;		
	}
	Vector2D operator*(float scalar){
		return Vector2D(m_x * scalar, m_y * scalar);
	}
	
	Vector2D& operator*=(float scalar){
		m_x *= scalar;
		m_y *= scalar;

		return *this;
	}
	
	Vector2D operator-(const Vector2D& v2) const{
		return Vector2D(m_x - v2.m_x, m_y - v2.m_y);
	}
	friend Vector2D& operator-=(Vector2D& v1, const Vector2D& v2){
		v1.m_x -= v2.m_x;
		v1.m_y -= v2.m_y;
		return v1;
	}
	
	Vector2D operator/(float scalar){
		return Vector2D(m_x/scalar,m_y/scalar);
	}

	Vector2D& operator/=(float scalar){
		m_x/=scalar;
		m_y/=scalar;
		return *this;
	}

	void normalize(){
		float l = length();
		if(l > 0){
			(*this) *= 1/l;
		}
	}
private:

	float m_x;
	float m_y;
};

#endif
