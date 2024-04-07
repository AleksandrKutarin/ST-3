// Copyright 2024 Kutarin Alexandr

#include "../include/TimedDoor.h"
#include <stdexcept>

DoorTimerAdapter::DoorTimerAdapter(TimedDoor &door) : door(door) {}

void DoorTimerAdapter::Timeout() { door.throwState(); }

TimedDoor::TimedDoor(int timeout) : iTimeout(timeout), isOpened(false) {
  adapter = new DoorTimerAdapter(*this);
}

bool TimedDoor::isDoorOpened() { return isOpened; }

void TimedDoor::unlock() {
  isOpened = true;
  adapter->Timeout();
}

void TimedDoor::lock() { isOpened = false; }

int TimedDoor::getTimeOut() const {
  if (!isOpened) {
    throw std::runtime_error("Door Timeout");
  }
  return 1;
}

void TimedDoor::throwState() { getTimeOut(); }

void Timer::tregister(int timeout, TimerClient *client) {
  client->Timeout();
  sleep(timeout);
}

void Timer::sleep(int timeout) {
    for (int i = 0; i < timeout; i++) {
        i--;
    }
}
