#include <snake.h>


Snake::Snake(const Point& p, const Point& dir){
	alive = true;
	head = new Head(p, dir);
	tail = head;
}

void Snake::move(){
	if (head->want_tail()){
		points++;
		PObject temp = new Body(Point(), tail);
		tail = temp;
		head->give_tail(false);
	}
	tail->move();
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
