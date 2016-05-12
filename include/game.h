#pragma once
#include <snake.h>
#include <object.h>
#include <unistd.h>

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
		bool makeFood();

		Snake snake;
		PObject food;
		char** map;
		char** map2;
		int points;
		int H;
		int W;
	};

}
