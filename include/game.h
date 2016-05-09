#pragma once
#include <ncurses.h>

struct Point{
	typedef Point& reference;
	Point(): x(), y(){};
	Point(int _x, int _y): x(_x), y(_y){};
	static Point randomPoint(int max_x, int max_y);
	static const Point dir_top;
	static const Point dir_right;
	static const Point dir_bottom;
	static const Point dir_left;

	friend Point operator+(const Point& left, const Point& right);
	friend bool operator==(const Point& left, const Point& right);
	friend bool operator!=(const Point& left, const Point& right);

	int x;
	int y;
};

class Game{
public:
	Game();
	int wait_key();
	void redraw();
	void loop();
	~Game();
private:
	char** map;
};