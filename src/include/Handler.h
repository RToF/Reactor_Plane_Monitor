#if !defined(HANDLER_H)
#define HANDLER_H
#include <vector>

class ThreadPool;
class subHandler;
class Channel;
class Handler
{
private:
    std::vector<subHandler*> subHandlers;
    ThreadPool *thpool;
public:
    Handler(int size);
    ~Handler();

    void addChannel(Channel*);
};


#endif // HANDLER_H
