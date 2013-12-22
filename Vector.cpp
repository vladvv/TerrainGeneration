#include "stdafx.h"
#include "Vector.h"

Vector::Vector()
{
	x = 0; y = 0; z = 0;
}

Vector::Vector(float x_in, float y_in, float z_in){
	x = x_in;
	y = y_in;
	z = z_in;
}


Vector::~Vector()
{
}


Vector Vector::add(Vector a, Vector b){
	Vector return_vector;
	return_vector.x = a.x + b.x;
	return_vector.y = a.y + b.y;
	return_vector.z = a.z + b.z;
	return return_vector;
}
Vector Vector::multiply(double coeff, Vector a){
	Vector return_vector;
	return_vector.x = a.x * coeff;
	return_vector.y = a.y * coeff;
	return_vector.z = a.z * coeff;
	return return_vector;
}
Vector Vector::subtract(Vector a, Vector b){
	Vector return_vector;
	return_vector.x = a.x - b.x;
	return_vector.y = a.y - b.y;
	return_vector.z = a.z - b.z;
	return return_vector;
}



Vector Vector::CalcNormal(Vector p1, Vector p2, Vector p3)
{
	Vector return_vec;
	Vector a = Vector::subtract(p2, p1);
	Vector b = Vector::subtract(p3,p1);

	//cross prodcut of a and b
	return_vec.x = a.y * b.z - a.z * b.y;
	return_vec.y = a.z * b.x - a.x * b.z;
	return_vec.z = a.x * b.y - a.y * b.x;


	//normalize
	double length = sqrt((return_vec.x * return_vec.x) + (return_vec.y * return_vec.y) + (return_vec.z * return_vec.z));
	return_vec.x /= length;
	return_vec.y /= length;
	return_vec.z /= length;
	return return_vec;
}