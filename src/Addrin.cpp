#include "include/Addrin.h"
#include <string.h>
#include <stdio.h>
Addrin::Addrin()
{
    memset(&addr,'\0', sizeof(addr));
    addr_len = sizeof(addr);
}

Addrin::Addrin(const char* ip, uint16_t port)
{
    memset(&addr, '\0', sizeof(addr));
    addr.sin_addr.s_addr = inet_addr(ip);
    addr.sin_port = htons(port);
    addr.sin_family = AF_INET;
    addr_len = sizeof(addr);
}

Addrin::~Addrin()
{
    printf("delete addrin");
}
