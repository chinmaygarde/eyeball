#pragma once

#include <cstdint>
#include <ostream>

#include "fml/macros.h"

namespace eyeball {

template <class T>
struct TSize {
  using Type = T;

  Type width = {};
  Type height = {};

  constexpr TSize() = default;

  constexpr TSize(Type p_width, Type p_height)
      : width(p_width), height(p_height) {}

  constexpr bool operator==(const TSize<T>& o) const {
    return width == o.width && height == o.height;
  }

  constexpr bool operator!=(const TSize<T>& o) const { return !(*this == o); }

  constexpr bool IsEmpty() const { return width == Type{} || height == Type{}; }
};

template <class T>
struct TPoint {
  using Type = T;

  Type x = {};
  Type y = {};

  constexpr TPoint() = default;

  constexpr TPoint(Type p_x, Type p_y) : x(p_x), y(p_y) {}

  constexpr bool IsZero() const { return x == Type{} && y == Type{}; }
};

template <class T>
struct TRect {
  using Type = T;

  TPoint<Type> origin;
  TSize<Type> size;

  constexpr TRect() = default;

  constexpr TRect(TPoint<Type> p_origin, TSize<Type> p_size)
      : origin(p_origin), size(p_size) {}
};

using Scalar = double;

using Size = TSize<Scalar>;
using ISize = TSize<int64_t>;
using UISize = TSize<uint64_t>;

using Point = TPoint<Scalar>;
using IPoint = TPoint<int64_t>;
using UIPoint = TPoint<uint64_t>;

using Rect = TRect<Scalar>;
using IRect = TRect<int64_t>;
using UIRect = TRect<uint64_t>;

}  // namespace eyeball

namespace std {

template <class T>
inline std::ostream& operator<<(std::ostream& out, const eyeball::TSize<T>& s) {
  out << "(" << s.width << ", " << s.height << ")";
  return out;
}

template <class T>
inline std::ostream& operator<<(std::ostream& out,
                                const eyeball::TPoint<T>& p) {
  out << "(" << p.x << ", " << p.y << ")";
  return out;
}

template <class T>
inline std::ostream& operator<<(std::ostream& out, const eyeball::TRect<T>& r) {
  out << "(" << r.origin << ", " << r.size << ")";
  return out;
}

}  // namespace std
