#include "include/Acceptor.h"
#include "include/EventLoop.h"
#include "include/Epoll.h"
#include "include/Channel.h"
#include "include/Sockfd.h"
#include "include/Addrin.h"
#include "include/Handler.h"
#include "include/util.h"
#include <thread>

Acceptor::Acceptor()
{
    eventloop = new EventLoop();
    ep = new Epoll();
    handler = new Handler(5);
}

Acceptor::~Acceptor()
{
    delete ep;
    delete eventloop;
}

void Acceptor::addChannel(Channel* cn)
{   
    std::function<void()> _cb = [this, cn](){
    Channel* clntChannel = cn->accept();
    handler->addChannel(clntChannel);
    printf("accept\n");
    fflush(stdout);
    };
    cn -> setevent(EPOLLIN);
    cn -> listen();
    cn -> setcallback(_cb);
    ep -> updateChannel(cn);
}

void Acceptor::startloop()
{
    eventloop->loop(ep);
}

void Acceptor::newConnection()
{

}






