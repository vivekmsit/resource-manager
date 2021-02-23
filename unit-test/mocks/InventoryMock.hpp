#ifndef INVENTORY_MOCK_HPP
#define INVENTORY_MOCK_HPP

#include "IInventory.hpp"

class InventoryMock: public IInventory {
public:
    MOCK_METHOD1(allocate, std::pair<bool, unsigned long>(std::string));
    MOCK_METHOD1(deallocate, bool(unsigned long));
    MOCK_METHOD1(list, std::vector<unsigned long>(std::string));
    MOCK_METHOD0(listAll, std::map<std::string, std::vector<unsigned long>>(void));
};

#endif // INVENTORY_MOCK_HPP
