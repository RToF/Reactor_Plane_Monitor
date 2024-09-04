#if !defined(SOCKFD_H)
#define SOCKFD_H
class Channel;
class Sockfd
{
private:
    int fd;
public:
    Sockfd();
    Sockfd(bool);
    Sockfd(int, bool);
    ~Sockfd();

    int getfd();
    void listen();
    void accept(Channel *);
    void setfd(int);
    void setnonblock();
//     Sockfd& operator=(Sockfd&& other) noexcept {
//     if (this != &other) {
//         // 清理当前对象的资源（如有必要）
//         // 移动右值对象的资源到当前对象
//         fd = other.fd;
//         other.fd = -1;  // 或者其他无效值，避免右值对象析构时关闭套接字
//     }
//     return *this;
// }
};



#endif // SOCKFD_H
