#include "fixtures_location.h"
#include "fml/mapping.h"
#include "gtest/gtest.h"
#include "image.h"

namespace eyeball {
namespace testing {

TEST(EyeballTest, CanLoadImage) {
  auto mapping =
      fml::FileMapping::CreateReadOnly(EYEBALL_ASSETS_LOCATION "airplane.jpg");
  ASSERT_TRUE(mapping);
  Image image(std::move(mapping));
  ASSERT_TRUE(image.IsValid());
  ASSERT_EQ(image.GetSize(), UISize(487, 378));
}

TEST(EyeballTest, CanIterateTiles) {
  auto mapping =
      fml::FileMapping::CreateReadOnly(EYEBALL_ASSETS_LOCATION "airplane.jpg");
  ASSERT_TRUE(mapping);
  Image image(std::move(mapping));
  ASSERT_TRUE(image.IsValid());
  ASSERT_EQ(image.GetSize(), UISize(487, 378));
  bool is_valid = false;
  image.IterateTiles({1000u, 1000u}, [&is_valid](const UIRect& window) -> bool {
    is_valid = window.size == UISize(487, 378);
    return true;
  });
  ASSERT_TRUE(is_valid);
}

}  // namespace testing
}  // namespace eyeball
