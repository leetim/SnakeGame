#pragma once
#include <Point.h>
#include <vector>

#define CHR_HEAD '&'
#define CHR_BODY 'O'
#define CHR_FOOD '%'
#define CHR_WALL '#'
#define CHR_NOTHING '.'

class Object;

class Food;
class Head;
class Body;

typedef Object* PObject;

class Object{
public:
	friend class Snake;
	friend class Game;
	friend void colide_all(PObject actor, const Point& target);
	// static const std::vector<PObject>& objects;
	virtual void move()=0;
	virtual void colide(PObject)=0;
	virtual void colide(Food*)=0;
	virtual void colide(Body*)=0;
	virtual void colide(Head*)=0;
	virtual ~Object(){};

	Point get_position();
	char get_char(){
		return ch;
	};
	bool is_on_map(){
		return on_map;
	}

	static void clear_dead();
	static void clear_all();


protected: 	
	static std::vector<PObject> obj;
	bool on_map;
	Point position;
	char ch;
};

class Food: public Object{
public:
	Food(){};
	Food(const Point& p);
	void move(){};
	void colide(PObject);
	void colide(Food*){};
	void colide(Body*){};
	void colide(Head*);
};

class Head: public Object{
public:
	Head(){};
	Head(const Point& p, const Point& direction);
	void move();
	void colide(PObject);
	void colide(Food*){};
	void colide(Body*);
	void colide(Head*){};
	void give_tail(bool t);
	bool want_tail();
	friend class Snake;
private:
	bool need_tail;
	Point direction;
};

class Body: public Object{
public:
	Body(){};
	Body(const Point& p, PObject n);
	void move();
	void colide(PObject);
	void colide(Food*){};
	void colide(Body*){};
	void colide(Head*);
private:
	PObject next;
	Point last;
};
