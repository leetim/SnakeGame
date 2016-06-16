#pragma once
#include <snake.h>
#include <object.h>
#include <unistd.h>
#include <vector>
#include <acts.h>
#include <ncurses.h>

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
		Game(int height, int widht);
		virtual ~Game();
		virtual int loop();
		virtual void do_act(ChangeDir*);
		virtual void do_act(NewSnake*);
		virtual void do_act(NewFood*);
		virtual void undo_act(ChangeDir*);
		virtual void undo_act(NewSnake*);
		virtual void undo_act(NewFood*);
		void make_map(int height, int widht);
	protected:
		std::vector<Snake*> snake;
		std::vector<PAct> acts;
		Snake* mySnake;
		PObject getFood();
		int wait_key();
		void redraw();
		char** map;
		int points;
		int H;
		int W;
		Point lr_window;
	private:

	};

}
