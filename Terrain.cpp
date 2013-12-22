#include "stdafx.h"
#include "Terrain.h"
#include "Vector.h"


const unsigned long RAND_MAX_PLUS_1 = RAND_MAX + 1;



Terrain::Terrain()
{
	reset();
	fault_step = .5;
	smooth_factor = .95;
	circleSize = 20;
	circle_displacement = 10;
	maxHeight = 0;
	random_height = 5;
}


Terrain::~Terrain()
{
}

void Terrain::Generate(Operation mode, int iterations)
{
	for(int i = 0; i < iterations; i++)
	{
		switch (mode)
		{
			case FAULT:
				FaultAlgorithm();
				break;
			case SMOOTH:
				Smooth(smooth_factor);
				break;
			case CIRCLES:
				CirclesAlgorithm();
			break;
		}
	}

}

void Terrain::FaultAlgorithm()
{
	//int x_bound = X_DIM * STEP;
	//int y_bound = Y_DIM * STEP;	

	//generate random point
	//int rand_x1 = rand() % X_DIM;
	//int rand_y1 = rand() % Y_DIM;

	int rand_x1 = random() * X_DIM;
	int rand_y1 = random() * Y_DIM;

	int rand_x2 = rand() % X_DIM;
	int rand_y2 = rand() % Y_DIM;

	float c = -rand_x1 * (rand_y2 - rand_y1) + rand_y1 * (rand_x2 - rand_x1);
	float a = (rand_y2 - rand_y1);
	float b = -(rand_x2 - rand_x1);

	//TRACE("\n %d, %d, %f", rand_x, rand_y, slope);

	//y intercept of line

	for(int x = 0; x < X_DIM; x++)
	{
		for(int y = 0; y < Y_DIM; y++)
		{
			if(a * (x - X_DIM/2) + b * (y - Y_DIM/2) -c > 0)
				points[x][y].y += fault_step;
			else
				points[x][y].y -= fault_step;
		}
	}


}


float Terrain::random()
{
  float scale=RAND_MAX+1.;
  float base=rand()/scale;
  float fine=rand()/scale;
  return base+fine/scale;
}

void Terrain::reset()
{
	for(int x = 0; x < X_DIM; x++)
	{
		for(int y = 0; y < Y_DIM; y++)
		{
			points[x][y].x = x * STEP;
			points[x][y].y = 0;
			points[x][y].z = y * STEP;
		}
	}

}

//band smoothing filter
void Terrain::Smooth(float k){
	//TRACE("\nSmoothing with factor: %f", k);

	for(int x = 1; x < X_DIM; x++)
	{
		for(int y = 0; y < Y_DIM; y++)
		{
			points[x][y].y = points[x-1][y].y * (1-k) + points[x][y].y * k;
		}
	}

	for(int x = X_DIM-2; x > -1; x--)
	{
		for(int y = 0; y < Y_DIM; y++)
		{
			points[x][y].y = points[x+1][y].y * (1-k) + points[x][y].y * k;
		}
	}

	for(int x = 0; x < X_DIM; x++)
	{
		for(int y = 1; y < Y_DIM; y++)
		{
			points[x][y].y = points[x][y-1].y * (1-k) + points[x][y].y * k;
		}
	}

	for(int x = 0; x < X_DIM; x++)
	{
		for(int y = Y_DIM; y > -1; y--)
		{
			points[x][y].y = points[x][y+1].y * (1-k) + points[x][y].y * k;
		}
	}
}


void Terrain::CirclesAlgorithm()
{
	Vector random;
	//int rand_x1 = random() * X_DIM;
	random.x = Terrain::random() * X_DIM;
	random.y = Terrain::random() * Y_DIM;


	
	for(int x = 0; x < X_DIM; x++)
	{
		for(int y = 0; y < Y_DIM; y++)
		{
			float pd = distance(random, Vector(x, y, 0)) * 2 / circleSize;	

			if (abs(pd) <= 1.0)
				points[x][y].y += circle_displacement/2 + cos(pd * 3.14) * circle_displacement/2;
		}
	}

}

float Terrain::distance(Vector p1, Vector p2)
{
	return sqrt( (p2.x - p1.x) * (p2.x - p1.x) + (p2.y - p1.y) * (p2.y - p1.y));
}

void Terrain::Clip(float maxHeight)
{
	for(int x = 0; x < X_DIM; x++)
	{
		for(int y = 0; y < Y_DIM; y++)
		{
			if(	points[x][y].y <= 0)
				points[x][y].y = 0;
		}
	}


}

void Terrain::Shift(float shiftAmount)
{
	for(int x = 0; x < X_DIM; x++)
	{
		for(int y = 0; y < Y_DIM; y++)
		{
				points[x][y].y += shiftAmount;
		}
	}
}


//Shifts the terrain up or down so the average height is 0
void Terrain::AverageHeight()
{
	float sum = 0;
	//first calculate average
	for(int x = 0; x < X_DIM; x++)
	{
		for(int y = 0; y < Y_DIM; y++)
		{
			sum += points[x][y].y;
		}
	}

	float average = sum / (X_DIM * Y_DIM);

	Shift(-average);



}

void Terrain::IncrementalGenerate()
{
	points[0][0].y = 0;
	//generate first row
	for(int x = 1; x < X_DIM; x++)
	{
		points[x][0].y = points[x-1][0].y + (random() - .5) * random_height;
	}
	//generate rest of points


	for(int y = 1; y < Y_DIM; y++)
	{
		for(int x = 0; x < X_DIM; x++)
		{
			float sum = 0;
			int count = 0;

			//add up relevant points
			if(x > 0)
			{
				count++;
				sum += points[x-1][y].y;

				count++;
				sum+= points[x-1][y-1].y;
			}

			sum += points[x][y-1].y;
			count++;

 
			points[x][y].y = (sum / count) + (random() - .5) * random_height;

		}
	}




}

void Terrain::RandomGenerate()
{

	for(int x = 0; x < X_DIM; x++)
	{
		for(int y = 0; y < Y_DIM; y++)
		{
			points[x][y].y += (random() - .5) * random_height;
		}
	}

}