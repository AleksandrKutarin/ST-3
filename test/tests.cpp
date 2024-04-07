// Copyright 2024 Kutarin Alexandr

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <cstdint>
#include "TimedDoor.h"

class MockTimerClient : public TimerClient {
 public:
  MOCK_METHOD(void, Timeout, ());
};

class TimedDoorTest : public ::testing::Test {
 protected:
  void SetUp() override {
    door = new TimedDoor(100);
  }

  void TearDown() override {
    delete door;
  }

  TimedDoor* door;
};
TEST(TimerTest, TimerClientRegistered) {
  Timer timer;
  MockTimerClient client;
  EXPECT_CALL(client, Timeout()).Times(1);
  timer.tregister(100, &client);
}
TEST_F(TimedDoorTest, isLockable) {
  door->unlock();
  door->lock();
  EXPECT_FALSE(door->isDoorOpened());
}

TEST_F(TimedDoorTest, isOpened) {
  door->unlock();
  EXPECT_TRUE(door->isDoorOpened());
}

TEST_F(TimedDoorTest, isClosed) {
  EXPECT_FALSE(door->isDoorOpened());
}

TEST_F(TimedDoorTest, TimeOutDoorClosedAndOpened) {
  door->unlock();
  door->lock();
  EXPECT_THROW(door->getTimeOut(), std::runtime_error);
  EXPECT_FALSE(door->isDoorOpened());
}

TEST_F(TimedDoorTest, TimeOutDoorOpenedUnlocked) {
  door->unlock();
  door->unlock();
  EXPECT_NO_THROW(door->getTimeOut());
  EXPECT_TRUE(door->isDoorOpened());
}

TEST_F(TimedDoorTest, TimeOutDoorClosed) {
  EXPECT_THROW(door->getTimeOut(), std::runtime_error);
  EXPECT_FALSE(door->isDoorOpened());
}

TEST_F(TimedDoorTest, TimeOutDoorOpened) {
  door->unlock();
  EXPECT_NO_THROW(door->getTimeOut());
  EXPECT_TRUE(door->isDoorOpened());
}
