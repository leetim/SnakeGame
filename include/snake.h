#pragma once
#include <object.h>
#include <vector>

class Snake{
public:
	Snake(){};
	Snake(const Snake& other): head(other.head), tail(other.tail),
	body(other.body), alive(other.alive), points(other.points){};
	Snake(std::vector<Point>&& points, Point dir);
	Snake(const Point& p, const Point& dir);
	void move();
	bool is_alive();
	void add_new_dir(const Point& dir);
	PObject operator[](int i);
	unsigned int count();
	Point head_coord();
	Point head_dir();
	int get_points();
private:
	Head* head;
	PObject tail;
	std::vector<PObject> body;
	bool alive;
	unsigned int points;
};
