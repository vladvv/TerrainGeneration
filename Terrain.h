//#pragma once
#include "Vector.h"

#define X_DIM 100
#define Y_DIM 100
#define STEP 2




class Terrain
{
public:

	float fault_step;
	float smooth_factor;
	float circleSize;
	float circle_displacement;
	float maxHeight;
	float random_height;

	enum Operation {FAULT, SMOOTH, CIRCLES};
	Vector points[X_DIM][Y_DIM];
	
	static const int x_dimension = X_DIM;
	static const int y_dimension = Y_DIM;
	void Terrain::IncrementalGenerate();
	float Terrain::distance(Vector p1, Vector p2);

	Terrain();
	~Terrain();

	void Generate(Operation mode, int iterations);
	
	void Terrain::reset();
	void Terrain::Smooth(float k);
	float random();
	void FaultAlgorithm();
	void Terrain::CirclesAlgorithm();
	void Terrain::Clip(float maxHeight);
	void Terrain::Shift(float shiftAmount);
	void Terrain::AverageHeight();
	void Terrain::RandomGenerate();
};



