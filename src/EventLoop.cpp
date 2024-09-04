#include "./include/EventLoop.h"
#include "./include/Epoll.h"


EventLoop::EventLoop()
{
    quit = false;
}

EventLoop::~EventLoop()
{

}

void EventLoop::loop(Epoll* ep)
{
    while(!quit)
    {
        callbackChannels = ep->get();
        for(auto it = callbackChannels.begin(); it != callbackChannels.end(); ++it)
        {
            (*it)->usecallback();
        }
    }
}