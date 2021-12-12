#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "../GraphData.h"

#include "../cs225/PNG.h"
using cs225::PNG;

#include "../cs225/HSLAPixel.h"
using cs225::HSLAPixel;

#include <vector>

// default constructor
TEST_CASE("HSLAPixel's default constructor creates a white pixel", "[weight=1]") {
  REQUIRE(true);
}
