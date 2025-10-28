#ifndef POSITION_H
#define POSITION_H

struct MyVector {
  float x, y;

  MyVector(float x = 0, float y = 0) : x(x), y(y) {}

  MyVector operator+(const MyVector &other) const {
    return {x + other.x, y + other.y};
  }
  MyVector operator-(const MyVector &other) const {
    return {x - other.x, y - other.y};
  }
};
#endif // POSITION_H
