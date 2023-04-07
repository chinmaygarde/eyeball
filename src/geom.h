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

  TSize() = default;

  TSize(Type w, Type h) : width(w), height(h) {}

  constexpr bool operator==(const TSize<T>& o) const {
    return width == o.width && height == o.height;
  }

  constexpr bool operator!=(const TSize<T>& o) const { return !(*this == o); }
};

using Scalar = double;

using Size = TSize<Scalar>;
using ISize = TSize<int64_t>;
using UISize = TSize<uint64_t>;

}  // namespace eyeball

namespace std {

template <class T>
inline std::ostream& operator<<(std::ostream& out, const eyeball::TSize<T>& s) {
  out << "(" << s.width << ", " << s.height << ")";
  return out;
}

}  // namespace std
