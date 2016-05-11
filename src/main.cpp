#include <iostream>
#include <time.h>
#include <game.h>
#include <stdlib.h>
#include <ncurses.h>

using namespace std;


int main(){
	srand(time(0));
	initscr();
	halfdelay(1);
	noecho();

	addch('K');
	myGame::Game game;
	game.loop();
	
	endwin();
	return 0;
}