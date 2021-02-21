#ifndef RESOURCE_MANAGER_HPP
#define RESOURCE_MANAGER_HPP

#include "IResourceManager.hpp"
#include "IInventory.hpp"
#include <memory>

class ResourceManager : public IResourceManager {
public:
    virtual ~ResourceManager(){}
    ResourceManager(std::shared_ptr<IInventory> inventory);
    std::pair<bool, unsigned long> handleAllocateRequest(std::string userName) override;
    bool handleDeallocateRequest(unsigned long resourceId) override;
    std::vector<unsigned long> handleListRequest(std::string userName) override;
    std::map<std::string, std::vector<unsigned long>> handleListAllRequest() override;
private:
    std::shared_ptr<IInventory> mInventory;
};

#endif // RESOURCE_MANAGER_HPP
