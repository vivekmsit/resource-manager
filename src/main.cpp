#include <iostream>

#include "Inventory.hpp"
#include "ResourceManager.hpp"
#include "HttpServer.hpp"

#include <csignal>
#include <thread>

volatile std::sig_atomic_t  g_shutdownPending = 0;

void signalHandler(int signal) {
    g_shutdownPending = signal;
}

static int run() {
    // Register signals for shutdown procedure..
    std::signal(SIGINT, signalHandler);
    std::signal(SIGTERM, signalHandler);

    while (g_shutdownPending == 0) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

int main() {
    std::cout<<"main start()"<<std::endl;
    unsigned long M = 10; // max resources per user
    unsigned long N = 50; // max number of resources
    auto inventory = std::make_shared<Inventory>(M, N);
    auto resourceManager = std::make_shared<ResourceManager>(inventory);
    auto httpServer = std::make_shared<HttpServer>(resourceManager);
    httpServer->start();
    int returnCode = run();
    httpServer->stop();
    std::cout<<"main end()"<<std::endl;
    return returnCode;
}
