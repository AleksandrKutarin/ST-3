// Copyright 2024 Kutarin Alexandr

#include <stdexcept>
#include <thread>
#include <chrono>

#include "TimedDoor.h"

DoorTimerAdapter::DoorTimerAdapter(TimedDoor& door) : door(door) {}

void DoorTimerAdapter::Timeout() {
  if (door.isDoorOpened()) {
    door.throwState();
  }
}

TimedDoor::TimedDoor(int timeout) : iTimeout(timeout), opened(false) {
  adapter = new DoorTimerAdapter(*this);
}

bool TimedDoor::isDoorOpened() {
  return isOpened;
}

void TimedDoor::unlock() {
  isOpened = true;
  Timer timer;
  timer.tregister(iTimeout, adapter);
}

void TimedDoor::lock() {
  isOpened = false;
}

void TimedDoor::getTimeOut() {
  if (isOpened) {
    throwState();
  }
}

void TimedDoor::throwState() {
  throw std::runtime_error("Door has been opened for too long");
}

void Timer::tregister(int timeout, TimerClient* client) {
  this->client = client;
  sleep(timeout);
}

void Timer::sleep(int timeout) {
  std::this_thread::sleep_for(std::chrono::seconds(timeout));
  client->Timeout();
}
