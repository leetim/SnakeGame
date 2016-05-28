#include <Point.h>
#include <stdlib.h>
#include <cmath>
#include <iostream>
#define MAAAX 1000000

using namespace std;

const Point Point::dir_top = Point(0, -1);
const Point Point::dir_left = Point(-1, 0);
const Point Point::dir_bottom = Point(0, 1);
const Point Point::dir_right = Point(1, 0);

Point::Point(const Point& other){
	x = other.x;
	y = other.y;
}

Point Point::randomPoint(int max_x, int max_y){
	double v1 = 2*((double)(rand()%MAAAX))/MAAAX - 1;
	double v2 = 2*((double)(rand()%MAAAX))/	MAAAX - 1;
	double s = sqrt(v1*v1 + v2*v2);
	if (s > 1){
		return randomPoint(max_x, max_y);
	}
	double u1 = v1*sqrt(-2*log(s)/s);
	double u2 = v2*sqrt(-2*log(s)/s);
	u1 = u1;
	u2 = u2;
	int x = ceil(max_x*u1);
	int y = ceil(max_y*u2);
	return Point(x, y);
}

Point& Point::operator=(const Point& other){
	x = other.x;
	y = other.y;
	return *this;
}

int Point::len2(){
	return x*x + y*y;
}

Point Point::operator-(){
	return Point(-x, -y);
}

Point operator+(const Point& l, const Point& r){
	return Point(l.x + r.x, l.y + r.y);
}


Point operator-(const Point& l, const Point& r){
	return Point(l.x - r.x, l.y - r.y);
}

bool operator==(const Point& l, const Point& r){
	return (l.x == r.x)&&(l.y == r.y);
}

bool operator!=(const Point& l, const Point& r){
	return !(l == r);
}


bool operator<(const Point& l, const Point& r){
	return (l.x < r.x && l.y < r.y) && l != r;
}
bool operator>(const Point& l, const Point& r){
	return (l.x > r.x && l.y > r.y) && l != r;
}
