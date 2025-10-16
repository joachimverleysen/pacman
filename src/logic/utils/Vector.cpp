#include "Vector.h"
#include <cmath>

Vector::Vector(const Position &start, const Position &end)
    : start(start), end(end), dx(end.x - start.x), dy(end.y - start.y) {}

float Vector::getMagnitude() const { return std::sqrt(dx * dx + dy * dy); }

Vector Vector::operator+(const Vector &other) const {
  Position newStart = start;
  Position newEnd(end.x + other.dx, end.y + other.dy);
  return Vector(newStart, newEnd);
}

Vector Vector::operator-(const Vector &other) const {
  Position newStart = start;
  Position newEnd(end.x - other.dx, end.y - other.dy);
  return Vector(newStart, newEnd);
}

Vector Vector::operator*(float scalar) const {
  Position newStart = start;
  Position newEnd(start.x + dx * scalar, start.y + dy * scalar);
  return Vector(newStart, newEnd);
}
