#include "include/Handler.h"
#include "include/Channel.h"
#include "include/subHandler.h"
#include "include/ThreadPool.h"

Handler::Handler(int size)
{
    thpool = new ThreadPool(size);
    for (int i = 0; i < size; i++)
    {   
        subHandler *handle = new subHandler();
        subHandlers.emplace_back(handle);
        std::function<void()> cb_ = std::bind(&subHandler::startloop,handle);
        thpool->add(cb_);
        
    }
    

}

Handler::~Handler()
{
    delete thpool;
}

void Handler::addChannel(Channel* cn)
{
    // int randinx = 1;
    subHandlers[0]->addChannel(cn);
    // subHandlers[0]->startloop();
}