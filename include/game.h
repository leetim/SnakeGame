#pragma once
#include <snake.h>
#include <object.h>
#include <unistd.h>
#include <vector>

namespace myGame{

	class finishGame{
	public:
		finishGame(){};
		bool operator()(){
			return true;
		};
	};

	class Game{
	public:
		Game(int height, int weight);
		~Game();
		int loop();
	private:
		int wait_key();
		void redraw();
		PObject getFood();

		Snake snake;
		char** map;
		int points;
		int H;
		int W;
		Point lr_window;
	};

}
