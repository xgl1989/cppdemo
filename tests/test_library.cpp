#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include "library.h"

TEST_CASE("create_directory", "[single-file]") {
    REQUIRE(create_directory("newDirectory"));
}