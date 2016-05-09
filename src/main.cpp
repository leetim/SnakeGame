#include <iostream>
#include <unistd.h>
#include <game.h>

using namespace std;


int main(){
	initscr();
	int i = 0;
	halfdelay(10);
	noecho();
	int k;
	while (true){
		k = getch();
		if (k == 'q'){
			break;
		}
		clear();
		i++;
		move(5, 5);
		printw("%d", i);
		// usleep(100000);
	}
	endwin();
	// cout << k << endl;
	return 0;
}