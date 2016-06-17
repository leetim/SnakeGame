#pragma once

#include <string>
#include <thread>
#include <asio.hpp>
#include <mutex>
#include <game.h>
#include <chrono>
#include <queue>

using Clock = std::chrono::high_resolution_clock;
using TimePoint = std::chrono::time_point<Clock>;
using MS = std::chrono::milliseconds;

std::mutex out_lock;

class Talker{
public:
    typedef Talker* PTalker;
    typedef asio::ip::tcp::endpoint endpoint;
    typedef asio::ip::tcp tcp;
    typedef asio::ip::tcp::acceptor acceptor;
    typedef asio::ip::tcp::socket socket;

    static void accept_all();
    static void close_all();
    static void sender(PTalker t);
    static void reader(PTalker t);
    static PTalker at(int i){return talkers[i];};

    static endpoint ep;
    static asio::io_service service;

    Talker(Snake* s): snake(s), send_thread(sender, this),
    read_thread(reader, this), m_socket(service){
        send_thread.detach();
        read_thread.detach();
    };
    ~Talker();
    void change_dir_messege(Point new_dir, int number);
    void new_snake_messege(Snake*);
    void new_food_messege(Food*);

private:

    static std::vector<PTalker> talkers;
    static std::mutex talkers_lock;

    Snake* snake;
    socket m_socket;
    bool ready;
    std::thread send_thread;
    std::thread read_thread;
};

namespace myGame{

    int OKEY;
    int SNAKE_GAME;
    int GET_SNAKES;
    int GET_FOOD;
    int GET_MY_SNAKE_NUMBER;
    int END_MESSEGE;
    int NEXT;
    int START_CHANGES;
    int NEW_FOOD;
    int NEW_CLIENT;
    int CLEAR_DEAD;
    int CHANGE_DIR;
    int GET_CURRENT_TIME;
    TimePoint next_ping;
    TimePoint delta;
    MS tick_length(1000);

    class Client: public Game{
    public:

        Client(int height, int width);
        // virtual ~Client();
        virtual void make_step();
        virtual void back_to_step(ullong number);
        virtual void go_to_step(ullong number);
        virtual ullong get_current_step();
        virtual int loop();

        static void reader(Client* c);
        static void writer(Client* c);

    protected:
        std::mutex ping_lock;
        std::mutex object_lock;
        void read_snake();
        void read_food();
        void read_dir();

    private:
        Talker::socket m_socket;
    };

    class Server: public Client{
    public:
        Server(int max_connections);
        virtual ~Server();
        virtual void make_step();
        virtual void back_to_step(ullong number);
        virtual void go_to_step(ullong number);
        virtual ullong get_current_step();
        virtual int loop();
    protected:

    private:

    };
}
