#pragma once

#include "Message.h"

class MessagesHandler {
 public:
  virtual void handleMessage(Message* msg) = 0;

};
