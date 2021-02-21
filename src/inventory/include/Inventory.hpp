#ifndef INVENTORY_HPP
#define INVENTORY_HPP

#include "IInventory.hpp"

#include <map>
#include <vector>
#include <mutex>
#include <atomic>

class Inventory: public IInventory {
public:
    Inventory(unsigned long M, unsigned long N);
    std::pair<bool, unsigned long> allocate(std::string userName) override;
    virtual bool deallocate(unsigned long resourceId) override;
    std::vector<unsigned long> list(std::string userName) override;
    std::map<std::string, std::vector<unsigned long>> listAll() override;
private:
    std::map<unsigned long, std::string> mResourceIdToUserNameMapping;
    std::map<std::string, std::vector<unsigned long>> mUserNameToResourceIdsMapping;
    unsigned long mMaxResourcePerUser = 0;
    unsigned long mMaxNumberOfResources = 0;
    std::atomic<unsigned long> mCurrentAvailableResourceId = 1;
    std::mutex mMutex;
};

#endif // INVENTORY_HPP
