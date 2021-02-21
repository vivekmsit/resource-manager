#ifndef I_HTTP_SERVER_HPP
#define I_HTTP_SERVER_HPP

class IHttpServer {
public:
    virtual bool start() = 0;
    virtual bool stop() = 0;
};

#endif // I_HTTP_SERVER_HPP
