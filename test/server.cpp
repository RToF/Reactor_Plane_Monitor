#include "../src/include/Channel.h"
#include "../src/include/Acceptor.h"

int main(int argc, char const *argv[])
{
    Acceptor *acceptor = new Acceptor();
    Channel* cn = new Channel("127.0.0.1",1234);
    acceptor->addChannel(cn);
    acceptor->startloop();
    delete acceptor;
    return 0;
}
