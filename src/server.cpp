#include <server.h>
#include <iostream>

using namespace asio;
using namespace std;
using namespace myGame;

io_service Talker::service;
vector<Talker::PTalker> Talker::talkers;
// vector<Messege> Talker::messeges;
mutex Talker::talkers_lock;
// mutex Talker::messeges_lock;
// long long Talker::max_number = 0;
Talker::endpoint Talker::ep(Talker::tcp::v4(), 18008);

int OKEY = 1;
int SNAKE_GAME = 16;
int GET_SNAKES = 3325;
int GET_FOOD = 15234;
int GET_MY_SNAKE_NUMBER = 11221;
int END_MESSEGE = -1;
int NEXT = 2;
int START_CHANGES = 1928;
int NEW_FOOD = 12422;
int NEW_CLIENT = 2212;
int CLEAR_DEAD = 666;
int CHANGE_DIR = 1122;
int GET_CURRENT_TIME = 1122;

Talker::~Talker(){
    m_socket.shutdown(socket::shutdown_receive);
    m_socket.close();
}

void Talker::close_all(){
    for (std::size_t i = 0; i < talkers.size(); i++){
        delete talkers[i];
    }
}

void Talker::accept_all(){
    acceptor acc(service, ep);
    while (true){
        // PTalker t = new Talker;
        // acc.accept(t->m_socket);
        // talkers_lock.lock();
        // out_lock.lock();
        // cout << "new user connected" << endl;
        // out_lock.unlock();
        // talkers.push_back(t);
        // talkers_lock.unlock();
        // t->ready = true;
    }
}

void Talker::sender(Talker::PTalker t){
    while (!t->ready){}
    // while (t->m_socket.is_open()){
    //     messeges_lock.lock();
    //     for (std::vector<Messege>::iterator i = messeges.begin();
    //     i != messeges.end(); i++){
    //         if (i->number <= t->last_messege){
    //             continue;
    //         }
    //         t->m_socket.write_some(buffer(i->text.c_str(), i->text.size()));
    //         t->last_messege = i->number;
    //     }
    //     messeges_lock.unlock();
    // }
}

void Talker::reader(PTalker t){
    while (!t->ready){}
    // while (t->m_socket.is_open()){
    //     if (t->m_socket.available()<=0){
    //         continue;
    //     }
    //     out_lock.lock();
    //     cout << "new messege" << endl;
    //     string text;
    //     while (t->m_socket.available()){
    //         char buf[1024];
    //         t->m_socket.read_some(buffer(buf, 1024));
    //         text = string(buf);
    //     }
    //     messeges_lock.lock();
    //     cout << text << endl;
    //     messeges.push_back(Messege(text, max_number + 1));
    //     max_number++;
    //     cout << "done" << endl;
    //     messeges_lock.unlock();
    //     out_lock.unlock();
    //
    // }
}

////////////////////////////////////////////////////////////////////////////////
//Client

Client::Client(int height, int width): m_socket(Talker::service){
    make_map(height, width);
    m_socket.connect(Talker::ep);
    char buf[1024];
    int* ibuf = (int*)buf;
    ullong* ullbuf = (ullong*)buf;
    m_socket.read_some(buffer(ibuf, 1024));
    if ( *ibuf != SNAKE_GAME){
        throw "wrong server";
    }
    m_socket.write_some(buffer(&OKEY, sizeof(int)));
    m_socket.write_some(buffer(&GET_SNAKES, sizeof(int)));
    while (*ibuf != END_MESSEGE){
        read_snake();
        m_socket.read_some(buffer(ibuf, 1024));
    }
    m_socket.write_some(buffer(&GET_FOOD, sizeof(int)));
    while (*ibuf != END_MESSEGE){
        read_food();
        m_socket.read_some(buffer(ibuf, 1024));
    }
    m_socket.write_some(buffer(&GET_MY_SNAKE_NUMBER, sizeof(int)));
    m_socket.read_some(buffer(ibuf, 1024));
    mySnake = snake[*ibuf];
    m_socket.write_some(buffer(&GET_CURRENT_TIME, sizeof(int)));
    m_socket.read_some(buffer(ullbuf, 1024));
    TimePoint server_start = TimePoint(MS(*ullbuf));
    TimePoint client_now = Clock::now();
    delta = TimePoint(server_start - client_now);
}

// Client::~Client(){
    // this->Game::~Game();
// }

void Client::read_snake(){
    vector<Point> p;
    Point dir;
    int length;
    int xy[2];
    m_socket.read_some(buffer(&length, sizeof(int)));
    m_socket.read_some(buffer(xy, 2*sizeof(int)));
    dir = Point(xy[0], xy[1]);
    for (int i = 0; i < length; i++){
        m_socket.read_some(buffer(xy, 2*sizeof(int)));
        p.emplace_back(xy[0], xy[1]);
    }
    Snake* temp = new Snake(move(p), dir);
    snake.push_back(temp);
}

void Client::read_food(){
    int xy[2];
    m_socket.read_some(buffer(xy, 2*sizeof(int)));
    new Food(Point(xy[0], xy[1]));
}

void Client::read_dir(){
    int number;
    int xy[2];
    m_socket.read_some(buffer(&number, sizeof(int)));
    m_socket.read_some(buffer(xy, 2*sizeof(int)));
    snake[number]->add_new_dir(Point(xy[0], xy[1]));
}

void Client::reader(Client* c){
    Talker::socket& sock = c->m_socket;
    char buf[1024];
    while (true){
        int* ibuf = (int*)buf;
        sock.read_some(buffer(ibuf, 1024));
        c->object_lock.lock();
        if (*ibuf == NEW_FOOD){
            c->read_food();
        }
        if (*ibuf == NEW_CLIENT){
            c->read_snake();
        }
        if (*ibuf == CHANGE_DIR){
            c->read_dir();
        }
        c->object_lock.unlock();
    }
}

void Client::writer(Client* c){
    Talker::socket& sock = c->m_socket;
    while (true){
        if (next_ping <= Clock::now()){
            this_thread::sleep_until(next_ping);
        }
        c->object_lock.lock();
        out_lock.lock();
        Point new_dir = Point();
        int k = getch();
        if (k == 'a' || k == 'A'){
            new_dir = Point::dir_left;
        }
        if (k == 'w' || k == 'W'){
            new_dir = Point::dir_top;
        }
        if (k == 'd' || k == 'D'){
            new_dir = Point::dir_right;
        }
        if (k == 's' || k == 'S'){
            new_dir = Point::dir_bottom;
        }
        if (new_dir == Point()){
            continue;
        }
        c->mySnake->add_new_dir(new_dir);
        sock.write_some(buffer(&CHANGE_DIR, sizeof(int)));
        int xy[] = {new_dir.x, new_dir.y};
        sock.write_some(buffer(xy, 2*sizeof(int)));
        out_lock.unlock();
        c->object_lock.unlock();
    }
}

void Client::make_step(){
    for (u_int i = 0; i < snake.size(); i++){
        snake[i]->move();
    }
}

void Client::back_to_step(ullong number){

}

void Client::go_to_step(ullong number){

}

ullong Client::get_current_step(){
    return 0;
}

int Client::loop(){
    std::thread reader_thread(reader, this);
    std::thread writer_thread(writer, this);
    next_ping = Clock::now();
    try{
        while (true){
            if (next_ping <= Clock::now()){
                object_lock.lock();
                make_step();
                out_lock.lock();
                redraw();
                out_lock.unlock();
                object_lock.unlock();
                ping_lock.lock();
                next_ping += tick_length;
                ping_lock.unlock();
            }
            if (!mySnake->is_alive()){
                throw 1;
            }
        }
    }
    catch(int e){
        clear();
    }
    return mySnake->get_points();
}
