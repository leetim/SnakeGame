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
		Game();
		~Game();
		void loop();
	private:
		int wait_key();
		void redraw();
		PObject getFood();
		void makeFood();

		Snake snake;
		PObject food;
		char** map;
		char** map2;
		int turn;
	};

}
