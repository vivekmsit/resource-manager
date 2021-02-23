#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "ResourceManager.hpp"
#include "mocks/InventoryMock.hpp"

using namespace ::testing;

class ResourceManagerTest: public ::testing::Test {
public:
    virtual  void SetUp() {
        inventoryMock = std::make_shared<InventoryMock>();
        resourceManager = std::make_shared<ResourceManager>(inventoryMock);
    }

    virtual void TearDown() {

    }
    std::shared_ptr<InventoryMock> inventoryMock;
    std::shared_ptr<ResourceManager> resourceManager;
};

TEST_F(ResourceManagerTest, AllocateAPIest) {
    std::string userName = "user1";
    auto result = std::make_pair<bool, unsigned long>(true, 1);
    EXPECT_CALL(*inventoryMock, allocate(_)).Times(1).WillOnce(Return(result));
    EXPECT_EQ(resourceManager->handleAllocateRequest(userName), result);
}

TEST_F(ResourceManagerTest, DeallocateAPITest) {
    unsigned long resourceId = 1;
    EXPECT_CALL(*inventoryMock, deallocate(_)).Times(1).WillOnce(Return(true));
    EXPECT_EQ(resourceManager->handleDeallocateRequest(resourceId), true);
}

TEST_F(ResourceManagerTest, ListAPITest) {
    std::string userName = "user1";
    auto result = std::vector<unsigned long>({});
    EXPECT_CALL(*inventoryMock, list(_)).Times(1).WillOnce(Return(result));
    EXPECT_EQ(resourceManager->handleListRequest(userName), result);
}

TEST_F(ResourceManagerTest, ListAllAPITest) {
   std::map<std::string, std::vector<unsigned long>> result;
   EXPECT_CALL(*inventoryMock, listAll()).Times(1).WillOnce(Return(result));
   EXPECT_EQ(resourceManager->handleListAllRequest(), result);
}