#pragma once
#include <Point.h>
#define LEFT_CODE 0
#define TOP_CODE 1
#define RIGHT_CODE 2
#define BOTTOM_CODE 3

typedef unsigned long long ullong;
namespace myGame{
    class Game;
}

class Act{
public:
    Act(): step(){};
    Act(ullong s): step(s){};
    virtual ~Act(){};
    ullong step;

    virtual void undo_act(myGame::Game* other)=0;
    virtual void do_act(myGame::Game* other)=0;
};

typedef Act* PAct;

class ChangeDir: public Act{
public:
    ChangeDir(): Act(), snake_num(), last_dir(), new_dir(){};
    ChangeDir(ullong _step, int _num, int _ldir, int _ndir):
    Act(_step), snake_num(_num), last_dir(_ldir), new_dir(_ndir){};
    int snake_num;
    int last_dir;
    int new_dir;

    void undo_act(myGame::Game* other);
    void do_act(myGame::Game* other);
};

class NewSnake: public Act{
    NewSnake(): Act(), snake_num(), coord(){};
    NewSnake(ullong _step, int _num, const Point& _coord):
    Act(_step), snake_num(_num), coord(_coord){};
    NewSnake(ullong _step, int _num, int x, int y):
    Act(_step), snake_num(_num), coord(x, y){};
    int snake_num;
    Point coord;

    void undo_act(myGame::Game* other);
    void do_act(myGame::Game* other);
};

class NewFood: public Act{
    NewFood(): Act(), food_num(), coord(){};
    NewFood(ullong _step, int _num, const Point& _coord):
    Act(_step), food_num(_num), coord(_coord){};
    NewFood(ullong _step, int _num, int x, int y):
    Act(_step), food_num(_num), coord(x, y){};
    int food_num;
    Point coord;

    void undo_act(myGame::Game* other);
    void do_act(myGame::Game* other);
};
