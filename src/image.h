#pragma once

#include <memory>

#include "fml/macros.h"
#include "fml/mapping.h"
#include "geom.h"

namespace eyeball {

class Image {
 public:
  Image(std::shared_ptr<fml::Mapping> compressed_mapping);

  ~Image();

  bool IsValid() const;

  UISize GetSize() const;

  using TileCallback = std::function<bool(const UIRect& window)>;
  void IterateTiles(UISize tile_size, TileCallback tile_cb) const;

 private:
  bool is_valid_ = false;
  UISize size_;
  std::shared_ptr<fml::Mapping> decompressed_image_;

  FML_DISALLOW_COPY_AND_ASSIGN(Image);
};

}  // namespace eyeball
