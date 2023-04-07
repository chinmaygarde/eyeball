#include "image.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "fml/logging.h"

namespace eyeball {

Image::Image(std::shared_ptr<fml::Mapping> compressed_mapping) {
  if (!compressed_mapping || !compressed_mapping->GetMapping()) {
    return;
  }
  int width = 0;
  int height = 0;
  int channels_in_file = 0;

  auto* decoded = ::stbi_load_from_memory(compressed_mapping->GetMapping(),  //
                                          compressed_mapping->GetSize(),     //
                                          &width,                            //
                                          &height,                           //
                                          &channels_in_file,                 //
                                          4                                  //
  );

  if (!decoded) {
    FML_LOG(ERROR) << "Could not decode image.";
    return;
  }

  decompressed_image_ = std::make_shared<fml::NonOwnedMapping>(
      decoded,                                               //
      width * height * channels_in_file,                     //
      [decoded](auto, auto) { ::stbi_image_free(decoded); }  //
  );
  size_ = {static_cast<UISize::Type>(width), static_cast<UISize::Type>(height)};
  is_valid_ = true;
}

Image::~Image() = default;

bool Image::IsValid() const {
  return is_valid_;
}

UISize Image::GetSize() const {
  return size_;
}

}  // namespace eyeball
