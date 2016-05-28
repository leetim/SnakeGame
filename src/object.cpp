#include <object.h>
#include <stdlib.h>

using namespace std;

///////////////////////////////////////////////////////////////////////////////////////////////////////
//Object

vector<PObject> Object::obj;

void colide_all(PObject actor, const Point& target){
	for (unsigned int i = 0; i < Object::obj.size(); i++){
		if (Object::obj[i]->position == target){
			actor->colide(Object::obj[i]);
		}
	}
}

void Object::clear_dead(){
	vector<PObject> temp;
	temp.reserve(obj.capacity());
	for (unsigned int i = 0; i < obj.size(); i++){
		if (obj[i]->on_map){
			temp.push_back(obj[i]);
		}
		else{
			delete obj[i];
		}
	}
	obj = temp;
}

void Object::clear_all(){
	for (unsigned int i = 0; i < obj.size(); i++){
		delete obj[i];
	}
	obj.assign(0, NULL);
}

Point Object::get_position(){
	return position;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////
//Food

Food::Food(const Point& p){
	ch = CHR_FOOD;
	position = p;
	obj.push_back(this);
	on_map = true;
}

void Food::colide(PObject o){
	o->colide(this);
}

void Food::colide(Head* o){
	on_map = false;
	o->give_tail(true);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////
//Head

Head::Head(const Point& p, const Point& dir){
	ch = CHR_HEAD;
	position = p;
	direction = dir;
	obj.push_back(this);
	on_map = true;
}

void Head::move(){
	Point temp = position + direction;
	colide_all(this, temp);
	position = temp;
}

void Head::colide(PObject o){
	o->colide(this);
}

void Head::colide(Body* o){
	this->on_map = false;
}

void Head::give_tail(bool t){
	need_tail = t;
}

bool Head::want_tail(){
	return need_tail;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////
//Body

Body::Body(const Point& p, PObject n){
	ch = CHR_BODY;
	position = p;
	next = n;
	obj.push_back(this);
	on_map = true;
}

void Body::move(){
	position = next->get_position();
	// next->move();
}

void Body::colide(PObject o){
	o->colide(this);
}

void Body::colide(Head* o){
	o->colide(this);
}
