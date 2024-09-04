#include "include/Channel.h"
#include "include/util.h"
#include "include/Sockfd.h"
#include "include/Addrin.h"
#include <sys/socket.h>
#include <sys/epoll.h>
#include <unistd.h>


Channel::Channel(){
    sockfd = new Sockfd(false);
    addr = new Addrin();
}

// specially for channel from server
Channel::Channel(const char* ip, uint16_t port)
{
    sockfd = new Sockfd(true);
    addr = new Addrin(ip, port);
    errif(::bind(sockfd->getfd(),(sockaddr*)&(addr->addr),addr->addr_len) == -1,"bind error");
}

// specially for channel from client
// Channel::Channel(int fd, const char* ip, uint16_t port)
// {   
//     sockfd = new Sockfd(fd, false);
//     addr = new Addrin(ip, port);
//     errif(bind(sockfd->getfd(),(sockaddr*)(&addr->addr),\
//             addr->addr_len) == -1,"bind error");
// }

Channel::~Channel()
{
    printf("delete channel");
    delete sockfd;
}

int Channel::getsockfd()
{
    return sockfd->getfd();
}

uint32_t Channel::getevent()
{
    return event;
}

void Channel::setevent(uint32_t ev)
{
    event |= ev;
}

Channel* Channel::accept()
{
    Channel *clntChannel = new Channel();
    sockfd->accept(clntChannel);
    // char* buf = "agaas";
    // write(clntChannel->getsockfd(), buf, sizeof(buf));
    return clntChannel;
}

void Channel::usecallback()
{
    callback();
}
void Channel::setcallback(std::function<void()> _cb)
{
    callback = _cb;
}

Addrin* Channel::getaddr()
{
    return addr;
}

void Channel::setsockfd(int fd)
{
    sockfd->setfd(fd);
}

void Channel::listen()
{
    sockfd->listen();
}

void Channel::setnonblock()
{
    sockfd->setnonblock();
}