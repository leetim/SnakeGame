#include <iostream>
#include <time.h>
#include <game.h>
#include <stdlib.h>
#include <ncurses.h>

using namespace std;


int main(){
	srand(time(0));
	initscr();
	noecho();
	int k = 0;

	while (k != 'q'){
		halfdelay(1);
		myGame::Game game(15, 15);
		int points = game.loop();
		move(6, 6);
		printw("You have %d points", points);		
		// halfdelay(-1);
		k = ERR;
		while (k == ERR){
			k = getch();			
		}
	}

	endwin();
	return 0;
}