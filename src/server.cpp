#include <server.h>

#define OK 1
#define SNAKE_GAME 16
#define GET_SNAKES 3325
#define GET_FOOD 15234
#define END_MESSEGE -1
#define NEXT 2

using namespace asio;
using namespace std;

io_service Talker::service;
vector<Talker::PTalker> Talker::talkers;
vector<Messege> Talker::messeges;
mutex Talker::talkers_lock;
mutex Talker::messeges_lock;
long long Talker::max_number = 0;
Talker::endpoint ep(Talker::tcp::v4(), 18008);

Talker::~Talker(){
    m_socket.shutdown(socket::shutdown_receive);
    m_socket.close();
}

static void Talker::close_all(){
    for (std::size_t i = 0; i < talkers.size(); i++){
        delete talkers[i];
    }
}

static void Talker::accept_all(){
    acceptor acc(service, ep);
    while (true){
        PTalker t = new Talker;
        acc.accept(t->m_socket);
        talkers_lock.lock();
        out_lock.lock();
        cout << "new user connected" << endl;
        out_lock.unlock();
        talkers.push_back(t);
        talkers_lock.unlock();
        t->ready = true;
    }
}

static void Talker::sender(Talker::PTalker t){
    while (!t->ready){}
    while (t->m_socket.is_open()){
        messeges_lock.lock();
        for (std::vector<Messege>::iterator i = messeges.begin();
        i != messeges.end(); i++){
            if (i->number <= t->last_messege){
                continue;
            }
            t->m_socket.write_some(buffer(i->text.c_str(), i->text.size()));
            t->last_messege = i->number;
        }
        messeges_lock.unlock();
    }
}

static void Talker::reader(PTalker t){
    while (!t->ready){}
    while (t->m_socket.is_open()){
        if (t->m_socket.available()<=0){
            continue;
        }
        out_lock.lock();
        cout << "new messege" << endl;
        string text;
        while (t->m_socket.available()){
            char buf[1024];
            t->m_socket.read_some(buffer(buf, 1024));
            text = string(buf);
        }
        messeges_lock.lock();
        cout << text << endl;
        messeges.push_back(Messege(text, max_number + 1));
        max_number++;
        cout << "done" << endl;
        messeges_lock.unlock();
        out_lock.unlock();

    }
}

////////////////////////////////////////////////////////////////////////////////
//Client

void Client::read_snake(){
    vector<Point>& p;
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
    Snake* temp = new Snake(p, dir);
    snake.push_back(temp);
}

void Client::read_food(){
    int xy[2];
    m_socket.read_some(buffer(xy, 2*sizeof(int)));
    new Food(xy[0], xy[1]);
}

Client::Client(int height, int width): m_socket(Talker::service){
    make_map(height, width);
    m_socket.connect(ep);
    char buf[1024];
    int* ibuf = (int*)buf;
    m_socket.read_some(buffer(ibuf, 1024));
    if ( *ibuf != SNAKE_GAME){
        throw "wrong server";
    }
    m_socket.write_some(buffer(OK));
    m_socket.write_some(buffer(GET_SNAKES));
    while (*ibuf != END_MESSEGE){
        read_snake();
        m_socket.read_some(buffer(ibuf, 1024));
    }
    m_socket.write_some(buffer(GET_FOOD));
    while (*ibuf != END_MESSEGE){
        read_food();
        m_socket.read_some(buffer(ibuf, 1024));
    }
}

Client::~Client(){

}

void reader(*Client c){

}

void writer(*Client c){

}

void Client::make_step(){
    for (int i = 0; i < snake.size(); i++){
        snake[i]->move();
    }
}

void Client::back_to_step(ulong number){

}

void Client::go_to_step(ulong number){

}

ulong Client::get_current_step(){

}

void Client::loop(){

}
