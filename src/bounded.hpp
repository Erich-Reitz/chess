#pragma once
#include "chess_exceptions.hpp"

template<typename T, T min, T max>
class bounded_value {
 private:
  T _value;
 public:
  bounded_value() {};
  bounded_value(T value) : _value(min) {
    if (value <= max && value >= min) {
      _value = value;
    } else {
      throw BoundConstraintViolation();
    }
  }
  ~bounded_value() {};
  bounded_value(const bounded_value<T, min, max> &b)
    : _value(b._value) { }

  operator const int &() const {
    return _value;
  }

  friend std::ostream &operator<< (std::ostream &stream, const bounded_value &bounded_value) {
    stream << bounded_value._value;
    return stream;
  }
};