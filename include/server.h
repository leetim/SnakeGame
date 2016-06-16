#pragma once

#include <string>
#include <thread>
#include <asio.hpp>
#include <mutex>
#include <game.h>


std::mutex out_lock;

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

private:
    Talker(): m_socket(service), last_messege(), ready(false),
    send_thread(sender, this), read_thread(reader, this){
        send_thread.detach();
        read_thread.detach();
    };

    ~Talker();

    static asio::io_service service;
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

class Client: public Game{
public:
    typedef unsigned long long ulong;
    Client();
    virtual ~Client();
    virtual void make_step();
    virtual void back_to_step(ulong number);
    virtual void go_to_step(ulong number);
    virtual ulong get_current_step();
    virtual void loop();
protected:

private:
    void read_snake();
    Talker::socket m_socket;
}

class Server: public Client{
public:
    typedef unsigned long long ulong;
    Server(int height, int width);
    virtual ~Server();
    virtual void make_step();
    virtual void back_to_step(ulong number);
    virtual void go_to_step(ulong number);
    virtual ulong get_current_step();
    virtual void loop();
protected:

private:

}
