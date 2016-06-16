#include <snake.h>

using namespace std;

Snake::Snake(const Point& p, const Point& dir){
	alive = true;
	head = new Head(p, dir);
	tail = head;
	body.push_back(head);
}

Snake::Snake(const vector<Point>& points, Point dir){
	alive = true;
	head = new Head(points.front(), dir);
	body.push_back(head);
	for (vector<Point>::iterator i = points.begin()+1; i != points.end(); i++){
		body.push_back(new Body(*i, body.back()));
	}
	tail = body.back();
	points = body.size() - 1;
}

void Snake::move(){
	if (head->want_tail()){
		points++;
		PObject temp = new Body(Point(), tail);
		tail = temp;
		body.push_back(tail);
		head->give_tail(false);
	}
	for (vector<PObject>::reverse_iterator i = body.rbegin(); i != body.rend(); i++){
		(*i)->move();
	}
}

bool Snake::is_alive(){
	return head->on_map;
}

void Snake::add_new_dir(const Point& dir){
	head->direction = dir;
}

PObject Snake::operator[](int i){
	return Object::obj[i];
}

unsigned int Snake::count(){
	return Object::obj.size();
}

Point Snake::head_coord(){
	return head->position;
}


Point Snake::head_dir(){
	return head->direction;
}


int Snake::get_points(){
	return body.size() - 1;
}
