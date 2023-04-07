#pragma once

#include <memory>

#include "fml/macros.h"
#include "fml/mapping.h"

namespace eyeball {

class Image {
 public:
  Image(std::shared_ptr<fml::Mapping> compressed_mapping);

  ~Image();

 private:
  FML_DISALLOW_COPY_AND_ASSIGN(Image);
};

}  // namespace eyeball
