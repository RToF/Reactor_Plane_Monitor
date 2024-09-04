#include "include/subHandler.h"
#include "include/EventLoop.h"
#include "include/Epoll.h"
#include "include/Channel.h"
#include "include/Sockfd.h"
#include "include/Addrin.h"
#include "include/Handler.h"
#include "include/util.h"
#include <unistd.h>
#include <string.h>
subHandler::subHandler()
{
    eventloop = new EventLoop();
    ep = new Epoll();
}

subHandler::~subHandler()
{
    delete ep;
    delete eventloop;
}

void subHandler::handle(int sockfd){
    char buf[10];
    while(true){    //由于使用非阻塞IO，读取客户端buffer，一次读取buf大小数据，直到全部读取完毕
        bzero(&buf, sizeof(buf));

        // char* buf = "agaas";
        // write(sockfd, buf, sizeof(buf));

        ssize_t bytes_read = read(sockfd, buf, sizeof(buf));
        buf[10] = '\0';
        if(bytes_read > 0){
            printf("message from client fd %d: %s\n", sockfd, buf);
            fflush(stdout);
            write(sockfd, buf, sizeof(buf));
        } else if(bytes_read == -1 && errno == EINTR){  //客户端正常中断、继续读取
            printf("continue reading");
                        fflush(stdout);
            continue;
        } else if(bytes_read == -1 && ((errno == EAGAIN) || (errno == EWOULDBLOCK))){//非阻塞IO，这个条件表示数据全部读取完毕
            printf("finish reading once, errno: %d\n", errno);
                        fflush(stdout);
            break;
        } else if(bytes_read == 0){  //EOF，客户端断开连接
            printf("EOF, client fd %d disconnected\n", sockfd);
                        fflush(stdout);
            close(sockfd);   //关闭socket会自动将文件描述符从epoll树上移除
            break;
        }
    }
}

void subHandler::addChannel(Channel* cn)
{   
    std::function<void()> _cb = std::bind(&subHandler::handle,this,cn->getsockfd());
    cn -> setcallback(_cb);
    cn -> setevent(EPOLLIN | EPOLLET);
    cn -> setnonblock();
    ep -> updateChannel(cn);
}

void subHandler::startloop()
{
    eventloop->loop(ep);
}







