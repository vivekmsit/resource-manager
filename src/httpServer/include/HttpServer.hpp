#ifndef HTTP_SERVER
#define HTTP_SERVER

#include "IHttpServer.hpp"
#include "IResourceManager.hpp"

#include <httpserver.hpp>

#include <memory>
#include <iostream>

class HttpServer: public IHttpServer {
public:
    HttpServer(std::shared_ptr<IResourceManager> resourceManager);
    bool start() override;
    bool stop() override;

private:
    std::shared_ptr<IResourceManager> mResourceManager;
    std::map<std::string, std::shared_ptr<httpserver::http_resource>> mHttpResourceMap;
    httpserver::webserver webServer;
};

#endif // HTTP_SERVER
