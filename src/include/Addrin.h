#if !defined(ADDRIN_H)
#define ADDRIN_H
#include <arpa/inet.h>


class Addrin
{
private:

public:
    struct sockaddr_in addr;
    socklen_t addr_len;
    Addrin();
    Addrin(const char* ip, uint16_t port);
    ~Addrin();
};

#endif // ADDRIN_H
