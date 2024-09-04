#if !defined(ACCEPTOR_H)
#define ACCEPTOR_H
#pragma once
#include <map>

class EventLoop;
class Epoll;
class Channel;
class Handler;
class Acceptor
{
private:
    // std::map<int ,Channel*> serverChannels;
    EventLoop* eventloop;
    Epoll *ep;
    Handler *handler;
public:
    Acceptor();
    ~Acceptor();

    void addChannel(Channel*);
    void startloop();
    void newConnection();
};

#endif // ACCEPTOR_H
