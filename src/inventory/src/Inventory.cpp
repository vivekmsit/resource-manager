#include "Inventory.hpp"
#include <iostream>
#include <algorithm>

Inventory::Inventory(unsigned long M, unsigned long N) :
        mMaxResourcePerUser(M),
        mMaxNumberOfResources(N) {
    std::cout << "Inventory initialized" << std::endl;
}

std::pair<bool, unsigned long> Inventory::allocate(std::string userName) {
    std::lock_guard <std::mutex> lk(mMutex);
    int resourceId = 0;
    if (mResourceIdToUserNameMapping.size() >= mMaxNumberOfResources) {
        return {false, resourceId};
    }
    if (mUserNameToResourceIdsMapping.find(userName) != mUserNameToResourceIdsMapping.end() &&
        mUserNameToResourceIdsMapping[userName].size() >= mMaxResourcePerUser) {
        return {false, resourceId};
    }
    resourceId = mCurrentAvailableResourceId;
    mResourceIdToUserNameMapping[resourceId] = userName;
    mUserNameToResourceIdsMapping[userName].push_back(resourceId);
    mCurrentAvailableResourceId++;
    return {true, resourceId};
}

bool Inventory::deallocate(unsigned long resourceId) {
    std::lock_guard <std::mutex> lk(mMutex);
    if (mResourceIdToUserNameMapping.find(resourceId) != mResourceIdToUserNameMapping.end()) {
        std::string userName = mResourceIdToUserNameMapping[resourceId];
        auto &resourceList = mUserNameToResourceIdsMapping.at(userName);
        auto it = std::find(resourceList.begin(), resourceList.end(), resourceId);
        if (it != resourceList.end()) {
            mUserNameToResourceIdsMapping[userName].erase(it);
            mResourceIdToUserNameMapping.erase(resourceId);
            return true;
        }
        return false;
    } else {
        false;
    }
}

std::vector<unsigned long> Inventory::list(std::string userName) {
    std::lock_guard <std::mutex> lk(mMutex);
    if (mUserNameToResourceIdsMapping.find(userName) != mUserNameToResourceIdsMapping.end()) {
        return mUserNameToResourceIdsMapping[userName];
    } else {
        return {};
    }
}

std::map <std::string, std::vector<unsigned long>> Inventory::listAll() {
    std::lock_guard <std::mutex> lk(mMutex);
    return mUserNameToResourceIdsMapping;
}
