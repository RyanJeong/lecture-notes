// event_handler.hpp
#pragma once

#include <functional>

class EventHandler {
  void SetCallback(std::function<void(int)> cb);
};
