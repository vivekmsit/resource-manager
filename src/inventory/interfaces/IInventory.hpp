#ifndef I_INVENTORY_HPP
#define I_INVENTORY_HPP

#include <utility>
#include <string>
#include <map>
#include <vector>

class IInventory {
public:
    virtual std::pair<bool, unsigned long> allocate(std::string userName) = 0;
    virtual bool deallocate(unsigned long resourceId) = 0;
    virtual std::vector<unsigned long> list(std::string userName) = 0;
    virtual std::map<std::string, std::vector<unsigned long>> listAll() = 0;
};

#endif // I_INVENTORY_HPP
