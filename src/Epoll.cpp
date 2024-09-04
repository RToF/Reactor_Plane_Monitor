// #include <stdio.h>
#include <sys/socket.h>
#include <string.h>
#include "include/Epoll.h"
#include "include/util.h"
// #include "include/util.h"
#include <unistd.h>



#define MAX_EVENTS 1024

Epoll::Epoll()
{
    epfd = epoll_create1(0);
    errif(epfd == -1,"create epoll");
    events = new epoll_event[MAX_EVENTS];
    memset(events,'\0',sizeof(events)*MAX_EVENTS);
}

Epoll::~Epoll()
{   
    //wait for all connet down
    printf("close epfd");
    close(epfd);
    delete []events;
}

void Epoll::updateChannel(Channel* cn)
{
    struct epoll_event ev;
    memset(&ev, '\0', sizeof(ev));
    ev.data.ptr = cn;
    ev.events = cn->getevent();
    errif(epoll_ctl(epfd, EPOLL_CTL_ADD, cn->getsockfd(), &ev) == -1,"epoll_ctl error");
}

std::vector<Channel*> Epoll::get()
{
    std::vector<Channel*> acns;
    int nfds = epoll_wait(epfd,events,MAX_EVENTS,-1);

    // if (nfds == -1 && errno == EINTR){
    //     printf("interupt");
    // }

    for (int i = 0; i < nfds; i++)
    {
        Channel *ch = (Channel*)events[i].data.ptr;
        acns.push_back(ch);
    }
    return acns;

}
