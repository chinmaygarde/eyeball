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

}  // namespace testing
}  // namespace eyeball
