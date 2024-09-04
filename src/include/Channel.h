#ifndef CHANNEL_H
#define CHANNEL_H
// #pragma once
#include <functional>
#include "Sockfd.h"
#include "Addrin.h"

class Channel
{
private:
    Sockfd* sockfd;
    Addrin* addr;
    uint32_t event;
    std::function<void()> callback;
public:
    Channel();
    Channel(const char*, uint16_t);
    // Channel(int, const char*, uint16_t);
    ~Channel();

    Channel* accept();
    int getsockfd();
    Addrin* getaddr();
    // void handlevent();
    uint32_t getevent();
    void setevent(uint32_t);
    void listen();
    void setsockfd(int);
    void setnonblock();
    void setcallback(std::function<void()>);
    void usecallback();
};


#endif