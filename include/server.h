#pragma once

#include <string>
#include <thread>
#include <asio.hpp>
#include <mutex>
#include <game.h>
#include <chrono>

using Clock = std::chrono::high_resolution_clock;
using TimePoint = std::chrono::time_point<Clock>;
using MS = std::chrono::milliseconds;

std::mutex out_lock;
// typedef unsigned long long ullong;

struct Messege{
    Messege(): number(), text(){};
    Messege(const Messege& m): number(m.number), text(m.text){};
    Messege(const std::string& str, const long long& num): number(num), text(str){};
    long long number;
    std::string text;
};

class Talker{
public:
    typedef Talker* PTalker;
    typedef asio::ip::tcp::endpoint endpoint;
    typedef asio::ip::tcp tcp;
    typedef asio::ip::tcp::acceptor acceptor;
    typedef asio::ip::tcp::socket socket;

    static void close_all();
    static void accept_all();
    static void sender(PTalker t);
    static void reader(PTalker t);

    static std::vector<Messege> messeges;
    static endpoint ep;
    static asio::io_service service;

private:
    Talker(): m_socket(service), last_messege(), ready(false),
    send_thread(sender, this), read_thread(reader, this){
        send_thread.detach();
        read_thread.detach();
    };

    ~Talker();

    static std::vector<PTalker> talkers;
    static long long max_number;
    static std::mutex talkers_lock;
    static std::mutex messeges_lock;

    socket m_socket;
    long long last_messege;
    bool ready;
    std::thread send_thread;
    std::thread read_thread;
};

namespace myGame{

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

        static int OKEY;
        static int SNAKE_GAME;
        static int GET_SNAKES;
        static int GET_FOOD;
        static int GET_MY_SNAKE_NUMBER;
        static int END_MESSEGE;
        static int NEXT;
        static int START_CHANGES;
        static int NEW_FOOD;
        static int NEW_CLIENT;
        static int CLEAR_DEAD;
        static int CHANGE_DIR;
        static int GET_CURRENT_TIME;
    protected:
        TimePoint next_ping;
        TimePoint delta;
        MS tick_length;
        std::mutex ping_lock;
        std::mutex object_lock;

    private:
        void read_snake();
        void read_food();
        void read_dir();
        Talker::socket m_socket;
    };

    class Server: public Client{
    public:
        Server(int height, int width);
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
