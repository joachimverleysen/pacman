#include "MyVector.h"
#ifndef VECTOR_H

struct Vector {
  MyVector start;
  MyVector end;
  float dx;
  float dy;

  Vector(const MyVector &start = {}, const MyVector &end = {});

  float getMagnitude() const;

  Vector operator+(const Vector &other) const;
  Vector operator-(const Vector &other) const;
  Vector operator*(float scalar) const;
};
#endif // ! VECTOR_H
