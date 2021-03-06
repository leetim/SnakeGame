#pragma once

struct Point{
	typedef Point& reference;
	Point(): x(), y(){};
	Point(int _x, int _y): x(_x), y(_y){};
	Point(const Point& other);
	reference operator=(const Point& other);
	Point operator-();
	int len2();

	static Point randomPoint(int max_x, int max_y);
	static const Point dir_top;
	static const Point dir_right;
	static const Point dir_bottom;
	static const Point dir_left;

	friend Point operator+(const Point& left, const Point& right);
	friend Point operator-(const Point& left, const Point& right);
	friend bool operator==(const Point& left, const Point& right);
	friend bool operator!=(const Point& left, const Point& right);
	//Семантика данных функций не совсем очивидна, смотрите код object.cpp
	//На экране если right лежит в правом нижнем секторе относительно left, то
	//возвращает тру
	friend bool operator<(const Point& left, const Point& right);
	friend bool operator>(const Point& left, const Point& right);

	int x;
	int y;
};
