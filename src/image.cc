#include "image.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

namespace eyeball {

Image::Image(std::shared_ptr<fml::Mapping> compressed_mapping) {}

Image::~Image() = default;

}  // namespace eyeball
