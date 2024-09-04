#ifndef EVENT_LOOP_H
#define EVENT_LOOP_H
#pragma once
#include <functional>
#include <vector>
class Epoll;
class Channel;
class EventLoop
{
private:
    bool quit;
    std::vector<Channel*> callbackChannels;
public:
    EventLoop();
    ~EventLoop();

    void loop(Epoll*);

    void add_channel();
    void remove_channel();
};

#endif