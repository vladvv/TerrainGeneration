#pragma once


class Vector 
{
private:
	
public:
	float x;
	float y;
	float z;
	
	static Vector add(Vector a, Vector b);
	static Vector multiply(double coeff, Vector a);
	static Vector subtract(Vector a, Vector b);
	static Vector CalcNormal(Vector p1, Vector p2, Vector p3);
	Vector();
	~Vector();
	Vector(float x_in, float y_in, float z_in);

	
	
};
