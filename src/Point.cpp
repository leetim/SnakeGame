#include <Point.h>
#include <stdlib.h>

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
	return Point(rand()%max_x, rand()%max_y);
}

Point& Point::operator=(const Point& other){
	x = other.x;
	y = other.y;
	return *this;
}


Point Point::operator-(){
	return Point(-x, -y);
}

Point operator+(const Point& l, const Point& r){
	return Point(l.x + r.x, l.y + r.y);
}

bool operator==(const Point& l, const Point& r){
	return (l.x == r.x)&&(l.y == r.y);
}

bool operator!=(const Point& l, const Point& r){
	return !(l == r);
}