#include <game.h>
#include <string>
#include <ncurses.h>


using namespace myGame;
using namespace std;

//////////////////////////////////////////////////////////////////////////////////////////////
//exception

//////////////////////////////////////////////////////////////////////////////////////////////
//Functions

char** getMap(int length, int height){
	length += 1;
	char** temp = new char*[height];
	char* temp2 = new char[height * length];
	for (int i = 0; i < height; i++){
		temp[i] = &temp2[length * i];
		temp2[length * (i + 1) - 1] = '\0';
	}
	return temp;
}

void deleteMap(char** ptr){
	delete[] ptr[0];
	delete[] ptr;
}

//////////////////////////////////////////////////////////////////////////////////////////////
//Game

Game::Game(int height, int weight){
	W = weight;
	H = height;
	snake = Snake(Point(0, 0), Point::dir_left);
	map = getMap(W, H);
	for (int i = 0; i < 3000; i++){
		getFood();
	}
	points = 0;
	for (int i = 0; i < H; i++){
		for (int j = 0; j < W; j++){
			map[i][j] = CHR_NOTHING;
			// map2[i][j] = map[i][j];
		}
	}
}

Game::~Game(){
	deleteMap(map);
	Object::clear_all();
}

int Game::wait_key(){
	int k = getch();
	Point new_dir;
	switch (k){
		case 'w':
			new_dir = Point::dir_top;
			break;
		case 'd':
			new_dir = Point::dir_right;
			break;
		case 's':
			new_dir = Point::dir_bottom;
			break;
		case 'a':
			new_dir = Point::dir_left;
			break;
		default:
			return -1;
	}
	if (snake.head_dir() != new_dir && -snake.head_dir() != new_dir){
		snake.add_new_dir(new_dir);
	}
	return k;
}

PObject Game::getFood(){
	int k = 0;
	int f = 0;
	while (k < 100){
		Point t = Point::randomPoint(100, 100);
		for (unsigned int i = 0; i < Object::obj.size(); i++){
			if (Object::obj[i]->get_position() == t){
				f = 1;
				break;
			}
		}
		if (!f){
			return new Food(t);
		}
		f = 0;
	}
	return NULL;
}

void write_chr(Point p, char ch){
		move(p.y, p.x);
		addch(ch);
}

void Game::redraw(){
	clear();
	move(1, 1);
	Point s = snake.head_coord();
	printw("Your points: %d (%d, %d)", snake.get_points(), s.x, s.y);
	for (int i = 0; i < H; i++){
		for (int j = 0; j < W; j++){
			map[i][j] = CHR_NOTHING;
		}
	}
	Point mid = Point(W/2, H/2);
	Point window_coord = s - mid;
	Point zero = Point(0, 0);
	Point rb = Point(W, H);
	for (vector<PObject>::iterator i = Object::obj.begin(); i != Object::obj.end(); i++){
		Point t = (*i)->get_position() - window_coord;
		if (zero < t && t < rb){
			map[t.y][t.x] = (*i)->get_char();
		}

	}
	for (int i = 0; i < H; i++){
		move(i + 3, 3);
		printw("%s", map[i]);
	}
	refresh();
}

int Game::loop(){
	try{
		while (true){
			wait_key();
			getFood();
			snake.move();
			Object::clear_dead();
			if (!snake.is_alive()){
				throw finishGame();
			}
			redraw();
			usleep(10000);
		}
	}
	catch(finishGame e){
		if (e()){
			clear();
			return snake.get_points();
		}
		else{
			return loop();
		}
	}
}
