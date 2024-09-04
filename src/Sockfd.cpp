#include <sys/socket.h>
#include <unistd.h>
#include <fcntl.h>
#include "include/Sockfd.h"
#include "include/util.h"
#include "include/Channel.h"
#include "include/Addrin.h"
#include <arpa/inet.h>
#include <sys/epoll.h>

Sockfd::Sockfd(): fd(-1) {}

Sockfd::Sockfd(int fd, bool block = true): fd(fd)
{
    errif(fd == -1,"fd == -1");
    int reuse = 1;
    setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse));
    // errif(sockfd == -1, "socket create error");
    if (!block)
    {
        fcntl(fd, F_SETFL, fcntl(fd, F_GETFL) | O_NONBLOCK);
    }
}

/* 
 * @param block whether to block
 */ 
Sockfd::Sockfd(bool block = true)
{
    fd = socket(AF_INET, SOCK_STREAM, 0);
    int reuse = 1;
    setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse));
    errif(fd == -1, "socket create error");
    if (!block)
    {
        fcntl(fd, F_SETFL, fcntl(fd, F_GETFL) | O_NONBLOCK);
    }

}

Sockfd::~Sockfd()
{
    if (fd != -1)
    {
        close(fd);
        fd = -1;
    }
    printf("delete sockfd");
    fflush(stdout);
}

int Sockfd::getfd()
{
    return fd;
}
void setnonblocking(int fd){
    fcntl(fd, F_SETFL, fcntl(fd, F_GETFL) | O_NONBLOCK);
}

void Sockfd::accept(Channel* cn)
{
    struct sockaddr_in &clntAddrin = cn->getaddr()->addr; 
    int clnt_sockfd = ::accept(fd, (sockaddr*)&clntAddrin, &cn->getaddr()->addr_len);
    errif(clnt_sockfd == -1, "socket accept error");
    cn->setsockfd(clnt_sockfd);
    
    // char buf[10] = "agaas";
    // write(clnt_sockfd, buf, sizeof(buf));

    printf("new client fd %d! IP: %s Port: %d\n", clnt_sockfd, \
    inet_ntoa(cn->getaddr()->addr.sin_addr), ntohs(cn->getaddr()->addr.sin_port));
}   

void Sockfd::setfd(int newfd)
{
    fd = newfd;
}

void Sockfd::listen()
{
    errif(::listen(fd,SOMAXCONN) == -1, "listen error");
}

void Sockfd::setnonblock()
{
    fcntl(fd, F_SETFL, fcntl(fd, F_GETFL) | O_NONBLOCK);
}