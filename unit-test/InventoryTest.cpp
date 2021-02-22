#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "Inventory.hpp"

using namespace ::testing;

class InventoryTest: public ::testing::Test {
public:
    virtual  void SetUp() {

    }

    virtual void TearDown() {

    }
};

TEST_F(InventoryTest, AllocateAPIBasicTest) {
    int M = 5;
    int N = 10;
    auto inventory = std::make_shared<Inventory>(M, N);
    std::string userName = "user1";
    auto [result, resourceId] = inventory->allocate(userName);
    EXPECT_EQ(result, true);
    EXPECT_EQ(resourceId, 1);
}

TEST_F(InventoryTest, AllocateAPIUserResourceLimitTest) {
    int M = 5;
    int N = 10;
    auto inventory = std::make_shared<Inventory>(M, N);
    std::string userName = "user1";
    int i = 1;
    while (i <= M) {
        auto [result, resourceId] = inventory->allocate(userName);
        EXPECT_EQ(result, true);
        EXPECT_EQ(resourceId, i);
        i++;
    }
    auto [result, resourceId] = inventory->allocate(userName);
    EXPECT_EQ(result, false);
}

TEST_F(InventoryTest, AllocateAPIOverallResourceLimitTest) {
    int M = 5;
    int N = 10;
    auto inventory = std::make_shared<Inventory>(M, N);
    std::string userName = "user1";
    int i = 1;
    while (i <= M) {
        auto [result, resourceId] = inventory->allocate(userName);
        EXPECT_EQ(result, true);
        EXPECT_EQ(resourceId, i);
        i++;
    }
    userName = "user2";
    i = 1;
    while (i <= M) {
        auto [result, resourceId] = inventory->allocate(userName);
        EXPECT_EQ(result, true);
        EXPECT_EQ(resourceId, M+i);
        i++;
    }
    userName = "user3";
    auto [result, resourceId] = inventory->allocate(userName);
    EXPECT_EQ(result, false);
}

TEST_F(InventoryTest, DeallocateAPIBasicTest) {
    int M = 5;
    int N = 10;
    auto inventory = std::make_shared<Inventory>(M, N);
    std::string userName = "user1";
    auto [result, resourceId] = inventory->allocate(userName);
    EXPECT_EQ(result, true);
    EXPECT_EQ(resourceId, 1);
    result = inventory->deallocate(resourceId);
    EXPECT_EQ(result, true);
}

TEST_F(InventoryTest, DeallocateAPIWithInvalidResourceID) {
    int M = 5;
    int N = 10;
    auto inventory = std::make_shared<Inventory>(M, N);
    std::string userName = "user1";
    auto [result, resourceId] = inventory->allocate(userName);
    EXPECT_EQ(result, true);
    EXPECT_EQ(resourceId, 1);
    result = inventory->deallocate(0xFFFF);
    EXPECT_EQ(result, false);
}

TEST_F(InventoryTest, ListAPIMultipleUsersTest) {
    int M = 5;
    int N = 10;
    auto inventory = std::make_shared<Inventory>(M, N);
    std::string userName1 = "user1";
    int i = 1;
    std::vector<unsigned long> firstUserResourceIds{};
    while (i <= M) {
        auto [result, resourceId] = inventory->allocate(userName1);
        EXPECT_EQ(result, true);
        EXPECT_EQ(resourceId, i);
        firstUserResourceIds.push_back(i);
        i++;
    }
    std::string userName2 = "user2";
    i = 1;
    std::vector<unsigned long> secondUserResourceIds{};
    while (i <= M) {
        auto [result, resourceId] = inventory->allocate(userName2);
        EXPECT_EQ(result, true);
        EXPECT_EQ(resourceId, M+i);
        secondUserResourceIds.push_back(M+i);
        i++;
    }
    EXPECT_EQ(inventory->list(userName1), firstUserResourceIds);
    EXPECT_EQ(inventory->list(userName2), secondUserResourceIds);
}

TEST_F(InventoryTest, ListAllAPIMultipleUsersTest) {
    int M = 5;
    int N = 10;
    auto inventory = std::make_shared<Inventory>(M, N);
    std::string userName1 = "user1";
    int i = 1;
    std::vector<unsigned long> firstUserResourceIds{};
    while (i <= M) {
        auto [result, resourceId] = inventory->allocate(userName1);
        EXPECT_EQ(result, true);
        EXPECT_EQ(resourceId, i);
        firstUserResourceIds.push_back(i);
        i++;
    }
    std::string userName2 = "user2";
    i = 1;
    std::vector<unsigned long> secondUserResourceIds{};
    while (i <= M) {
        auto [result, resourceId] = inventory->allocate(userName2);
        EXPECT_EQ(result, true);
        EXPECT_EQ(resourceId, M+i);
        secondUserResourceIds.push_back(M+i);
        i++;
    }
    auto resourceIdsList = inventory->listAll();
    EXPECT_NE(resourceIdsList.find(userName1), resourceIdsList.end());
    EXPECT_NE(resourceIdsList.find(userName2), resourceIdsList.end());
    EXPECT_EQ(resourceIdsList[userName1], firstUserResourceIds);
    EXPECT_EQ(resourceIdsList[userName2], secondUserResourceIds);
}
