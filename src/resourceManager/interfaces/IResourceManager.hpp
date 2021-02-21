#ifndef I_RESOURCE_MANAGER_HPP
#define I_RESOURCE_MANAGER_HPP

#include <utility>
#include <string>
#include <map>
#include <vector>

class IResourceManager {
public:
    virtual ~IResourceManager(){}
    virtual std::pair<bool, unsigned long> handleAllocateRequest(std::string userName) = 0;
    virtual bool handleDeallocateRequest(unsigned long resourceId) = 0;
    virtual std::vector<unsigned long> handleListRequest(std::string userName) = 0;
    virtual std::map<std::string, std::vector<unsigned long>> handleListAllRequest() = 0;
};

#endif // I_RESOURCE_MANAGER_HPP
