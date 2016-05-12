#include <game.h>
#include <string>
#include <ncurses.h>


using namespace myGame;

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
		temp2[length * i - 1] = '\0';
	}
	return temp;
}

void deleteMap(char** ptr){
	delete[] ptr[0];
	delete[] ptr;
}

PObject Game::getFood(){
	int k = 0;
	int f = 0;
	while (k < 100){
		Point t = Point::randomPoint(W, H);
		if (t.x != 0 && t.y != 0 && t.x != H - 1 && t.y != W - 1){
			for (unsigned int i = 0; i < snake.count(); i++){
				if (snake[i]->get_position() == t){
					f = 1;
					break;	
				}
			}
			if (!f){
				return new Food(t);
			}
			f = 0;
		}
	}
	return NULL;
}

//////////////////////////////////////////////////////////////////////////////////////////////
//Game

Game::Game(int height, int weight){
	W = weight;
	H = height;
	snake = Snake(Point(10, 5), Point::dir_left);
	map = getMap(W, H);
	map2 = getMap(W, H);
	food = getFood();
	points = 0;
	for (int i = 0; i < H; i++){
		for (int j = 0; j < W; j++){
			map[i][j] = ((i == 0 || j == 0 || i == H - 1 || j == W - 1) ? '#' : '.');
			map2[i][j] = map[i][j];
		}
	}
}

Game::~Game(){
	deleteMap(map);
	deleteMap(map2);
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

void Game::redraw(){
	clear();
	move(1, 1);
	printw("Your points: %d", points);
	for (unsigned int i = 0; i < snake.count(); i++){
		Point t = snake[i]->get_position();
		map[t.y][t.x] = snake[i]->get_char();	
	}
	for (int i = 0; i < H; i++){
		move(i + 3, 3);
		printw("%s", map[i]);
		for (int j = 0; j < W; j++){
			// addch(map[j][i]);
			map[i][j] = map2[i][j];
		}
	}
	refresh();
}


bool Game::makeFood(){
	if (food == NULL || !food->is_on_map()){
		food = getFood();
		return true;
	}
	return false;
}

int Game::loop(){
	try{
		while (true){
			wait_key();
			snake.move();
			if (makeFood()){
				points++;
			}
			Object::clear_dead();
			if (!snake.is_alive()){
				throw finishGame();
			}
			else{
				Point t = snake.head_coord();
				if (map2[t.y][t.x] == '#'){
					throw finishGame();
				}
			}
			redraw();
			usleep(50000);
		}
	}
	catch(finishGame e){
		if (e()){
			clear();
			return points;
		}
		else{
			return loop();
		}
	}
}
