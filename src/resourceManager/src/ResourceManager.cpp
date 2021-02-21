#include "ResourceManager.hpp"

 ResourceManager::ResourceManager(std::shared_ptr<IInventory> inventory): mInventory(inventory) {

}

std::pair<bool, unsigned long> ResourceManager::handleAllocateRequest(std::string userName) {
    return mInventory->allocate(userName);
}

bool ResourceManager::handleDeallocateRequest(unsigned long resourceId) {
    return mInventory->deallocate(resourceId);
}

std::vector<unsigned long> ResourceManager::handleListRequest(std::string userName) {
    return mInventory->list(userName);
}

std::map<std::string, std::vector<unsigned long>> ResourceManager::handleListAllRequest() {
    return mInventory->listAll();
}
