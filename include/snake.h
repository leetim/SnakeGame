#pragma once
#include <object.h>

class Snake{
public:
	Snake(){};
	Snake(const Point& p, const Point& dir);
	void move();
	bool is_alive();
	void add_new_dir(const Point& dir);
	PObject operator[](int i);
	unsigned int count();
	Point head_coord();
	Point head_dir();
private:
	Head* head;
	PObject tail;
	bool alive;
	unsigned int points;
};
