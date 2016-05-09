#include <game.h>
#include <stdlib.h>
#include <time.h>

using namespace std;

const Point Point::dir_top = Point(0, -1);
const Point Point::dir_left = Point(-1, 0);
const Point Point::dir_bottom = Point(0, 1);
const Point Point::dir_right = Point(1, 0);

char** getMap(int length, int height){
	char** temp = new char*[height];
	char* temp2 = new char[height * length];
	for (int i = 0; i < height; i++){
		temp[i] = &temp2[length * i];
	}
	return temp;
}

void deleteMap(char** ptr){
	delete[] ptr[0];
	delete[] ptr;
}

Point Point::randomPoint(int max_x, int max_y){
	srand(time(0));
	return Point(rand()%max_x, rand()%max_y);
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

