#if !defined(SUBHANDLER_H)
#define SUBHANDLER_H
#pragma once
#include <map>

class EventLoop;
class Epoll;
class Channel;
class subHandler
{
private:
    EventLoop* eventloop;
    Epoll *ep;
public:
    subHandler();
    ~subHandler();

    void addChannel(Channel*);
    void startloop();
    void handle(int);
    // void newConnection();
};

#endif // SUBHANDLER_H
