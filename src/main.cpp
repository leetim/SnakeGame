#include <iostream>
#include <time.h>
#include <game.h>
#include <stdlib.h>
#include <ncurses.h>

using namespace std;


int main(int argc, char* argv[]){
	srand(time(0));
	initscr();
	noecho();
	int k = 0;
	int y = getmaxy(stdscr) - 4;
	int x = getmaxx(stdscr) - 6;
	while (k != 'q'){
		halfdelay(1);
		myGame::Game game(y, x);
		int points = game.loop();
		move(6, 6);
		printw("You have %d points", points);
		k = ERR;
		while (k == ERR){
			k = getch();
		}
	}

	endwin();
	return 0;
}
