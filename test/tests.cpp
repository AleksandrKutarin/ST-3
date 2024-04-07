// Copyright 2024 Kutarin Alexandr

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <cstdint>
#include "TimedDoor.h"

class MockTimerClient : public TimerClient {
 public:
  MOCK_METHOD(void, Timeout, (), (override));
};

class TimedDoorTest : public ::testing::Test {
 protected:
  TimedDoor* door;
  MockTimerClient* client;

  void SetUp() override {
    client = new MockTimerClient();
    door = new TimedDoor(5);
  }

  void TearDown() override {
    delete door;
    delete client;
  }
};

TEST_F(TimedDoorTest, DoorInitiallyLocked) {
  EXPECT_FALSE(door->isDoorOpened());
}

TEST_F(TimedDoorTest, DoorUnlocks) {
  door->unlock();
  EXPECT_TRUE(door->isDoorOpened());
}

TEST_F(TimedDoorTest, DoorLocks) {
  door->unlock();
  door->lock();
  EXPECT_FALSE(door->isDoorOpened());
}

TEST_F(TimedDoorTest, TimeoutWhenDoorOpened) {
  door->unlock();
  EXPECT_CALL(*client, Timeout()).Times(1);
  door->getTimeOut();
}

TEST_F(TimedDoorTest, NoTimeoutWhenDoorClosed) {
  door->unlock();
  door->lock();
  EXPECT_CALL(*client, Timeout()).Times(0);
  door->getTimeOut();
}

TEST_F(TimedDoorTest, ThrowExceptionWhenTimeout) {
  door->unlock();
  EXPECT_THROW(door->getTimeOut(), std::runtime_error);
}

TEST_F(TimedDoorTest, NoExceptionWhenNoTimeout) {
  door->unlock();
  door->lock();
  EXPECT_NO_THROW(door->getTimeOut());
}

TEST_F(TimedDoorTest, ThrowExceptionWhenLockingClosedDoor) {
  EXPECT_THROW(door->lock(), std::logic_error);
}

TEST_F(TimedDoorTest, NoExceptionWhenUnlockingClosedDoor) {
  EXPECT_NO_THROW(door->unlock());
}

TEST_F(TimedDoorTest, CorrectTimeoutValue) {
  EXPECT_EQ(door->getTimeOut(), 5);
}
