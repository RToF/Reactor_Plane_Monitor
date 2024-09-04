#ifndef EPOLL_H
#define EPOLL_H
#pragma once
#include <sys/epoll.h>
#include "Channel.h"
#include <vector>

class Channel;
class Epoll
{
friend class A;
private:
    int epfd;
    struct epoll_event *events;
public:
    Epoll();
    ~Epoll();

    void updateChannel(Channel*);
    std::vector<Channel*> get();
    // void deleteChannel(Channel&);
};

#endif