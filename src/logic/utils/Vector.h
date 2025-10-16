#include "Position.h"
#ifndef VECTOR_H

struct Vector {
  Position start;
  Position end;
  float dx;
  float dy;

  Vector(const Position &start = {}, const Position &end = {});

  float getMagnitude() const;

  Vector operator+(const Vector &other) const;
  Vector operator-(const Vector &other) const;
  Vector operator*(float scalar) const;
};
#endif // ! VECTOR_H
