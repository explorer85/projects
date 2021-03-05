#ifndef UPDATABLE_H
#define UPDATABLE_H

class Updatable {
 public:
  virtual ~Updatable() = default;
  virtual void update() = 0;
};

#endif // UPDATABLE_H
