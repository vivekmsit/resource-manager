#include "HttpServer.hpp"
#include <iostream>
#include <string>
#include <functional>

class HttpAllocateResource : public httpserver::http_resource {
public:
    HttpAllocateResource(

            std::function<
            std::pair<bool, unsigned long>(std::string)

    > requestCallback):
    mRequestCallback(requestCallback){
    }

    const std::shared_ptr <httpserver::http_response> render(const httpserver::http_request &req) {
        std::cout << "HttpAllocateResource::render() received http request" << std::endl;
        std::string userName = req.get_arg("user");
        std::cout<<"user name is: " << userName << std::endl;
        auto[result, resourceId] = mRequestCallback(userName);
        std::string responseMessage = {};
        if (result) {
            responseMessage = std::to_string(resourceId);
        } else {
            responseMessage = "0";
        }
        return std::shared_ptr<httpserver::http_response>(
                new httpserver::string_response(responseMessage));
    }

private:
    std::function<
    std::pair<bool, unsigned long>(std::string
                                   userName)

    >
    mRequestCallback;
};

class HttpDeallocateResource : public httpserver::http_resource {
public:
    HttpDeallocateResource(

            std::function<
    bool(unsigned long)> requestCallback):
    mRequestCallback(requestCallback){
    }

    const std::shared_ptr <httpserver::http_response> render(const httpserver::http_request &req) {
        std::cout << "HttpDeallocateResource::render() received http request" << std::endl;
        std::string resourceIdString = req.get_arg("resourceId");
        std::cout<<"resource ID is: " << resourceIdString << std::endl;
        std::string responseMessage = "FAILURE";
        try {
            unsigned long resourceId = std::stoul(resourceIdString);
            auto result = mRequestCallback(resourceId);
            if (result) {
                responseMessage = "SUCCESS";
            }
        } catch (const std::invalid_argument &exception) {
            std::cerr << "Invalid argument exception: " << exception.what() << std::endl;
        }
        return std::shared_ptr<httpserver::http_response>(
                new httpserver::string_response(responseMessage));
    }

private:
    std::function<bool(unsigned long)> mRequestCallback;
};

class HttpListResource : public httpserver::http_resource {
public:
    HttpListResource(

            std::function<
            std::vector<unsigned long>(std::string)> requestCallback):
            mRequestCallback(requestCallback){
    }

    const std::shared_ptr <httpserver::http_response> render(const httpserver::http_request &req) {
        std::cout << "HttpDeallocateResource::render() received http request" << std::endl;
        std::string userName = req.get_arg("user");
        std::cout<<"user name is: " << userName << std::endl;
        std::string responseMessage = "";
        auto resourceIdList = mRequestCallback(userName);
        for (const auto& id: resourceIdList) {
            responseMessage += std::to_string(id) + ",";
        }
        return std::shared_ptr<httpserver::http_response>(
                new httpserver::string_response(responseMessage));
    }

private:
    std::function<std::vector<unsigned long>(std::string)> mRequestCallback;
};

class HttpListAllResource : public httpserver::http_resource {
public:
    HttpListAllResource(

            std::function<
                    std::map<std::string, std::vector<unsigned long>>(void)> requestCallback):
            mRequestCallback(requestCallback){
    }

    const std::shared_ptr <httpserver::http_response> render(const httpserver::http_request &req) {
        std::cout << "HttpDeallocateResource::render() received http request" << std::endl;
        std::string responseMessage = "";
        auto result = mRequestCallback();
        for (const auto& entry: result) {
            responseMessage += entry.first + ": [";
            for (const auto& element: entry.second) {
                responseMessage += std::to_string(element) + ",";
            }
            responseMessage += "],";
        }
        return std::shared_ptr<httpserver::http_response>(
                new httpserver::string_response(responseMessage));
    }

private:
    std::function<std::map<std::string, std::vector<unsigned long>>(void)> mRequestCallback;
};

HttpServer::HttpServer(std::shared_ptr <IResourceManager> resourceManager) :
        mResourceManager(resourceManager),
        webServer(httpserver::create_webserver(8080)) {
    mHttpResourceMap["allocate"] = std::make_shared<HttpAllocateResource>(
            std::bind(&IResourceManager::handleAllocateRequest, mResourceManager, std::placeholders::_1));
    mHttpResourceMap["deallocate"] = std::make_shared<HttpDeallocateResource>(
            std::bind(&IResourceManager::handleDeallocateRequest, mResourceManager, std::placeholders::_1));
    mHttpResourceMap["list"] = std::make_shared<HttpListResource>(
            std::bind(&IResourceManager::handleListRequest, mResourceManager, std::placeholders::_1));
    mHttpResourceMap["listAll"] = std::make_shared<HttpListAllResource>(
            std::bind(&IResourceManager::handleListAllRequest, mResourceManager));
}

bool HttpServer::start() {
    std::cout << "HttpServer::start()" << std::endl;
    for (auto &httpResourceEntry: mHttpResourceMap) {
        webServer.register_resource(httpResourceEntry.first, httpResourceEntry.second.get());
    }
    webServer.start(false);
    return true;
}

bool HttpServer::stop() {
    std::cout << "HttpServer::stop()" << std::endl;
    webServer.stop();
    return true;
}
