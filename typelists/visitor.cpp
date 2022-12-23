#include "visitor.h"


void AddTargetMessage::accept(MessagesVisitor &v) {
  v.visit(*this);
}
