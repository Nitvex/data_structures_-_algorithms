#include <stdio.h>
#include <math.h>
#include <vector>
#include "stdafx.h"

class Point{
public:
	int x;
	int y;

	Point(int _x, int _y) {	
		x = _x;
		y = _y;
	}

	double vectorLength(Point p) {	
		return sqrt((p.x - x) * (p.x - x) + (p.y - y) * (p.y - y));
	}
};

void main() {
	freopen("spantree.in", "r", stdin);
	freopen("spantree.out", "w", stdout);
	int n;
	scanf("%d", &n);
	Point* points = (Point*)malloc(sizeof(Point) * n);
	int tx, ty;
	for (int i = 0; i < n; i++) {	
		scanf("%d %d", &tx, &ty);
		points[i] = Point(tx, ty);
	}
	bool* outside = new bool[n]; //Points outside of tree
	int* distances = new int[n]; //Distances to points outside of tree
	for (int i = 1; i < n; i++) {	
		distances[i] = points[0].vectorLength(points[i]) * points[0].vectorLength(points[i]);
		outside[i] = true;
	}
	double spanpath = 0; //spanpath length
	int minpath, distance; //temp variables
	int point = 0; //last point added to tree
	while (true) //while there are points out of tree
	{
		//Finding nearest point to tree
		minpath = UINT_MAX;
		point = USHRT_MAX;
		for (int o = 1; o < n; ++o)
			if (outside[o] && distances[o] < minpath)
			{
				minpath = distances[o];
				point = o;
			}
		//Checking if all points are int tree
		if (point == USHRT_MAX)	break;
		//Adding it to tree
		outside[point] = false;
		spanpath += sqrt(minpath);
		//Recounting distances
		for (int o = 1; o < n; ++o)
			if (outside[o])
			{
				distance = points[point].vectorLength(points[o]) * points[point].vectorLength(points[o]);
				if (distance < distances[o])
					distances[o] = distance;
			}
	}
	printf("%.3lf\n", spanpath);
}