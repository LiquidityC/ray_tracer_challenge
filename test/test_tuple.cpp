#include <catch2/catch_test_macros.hpp>

extern "C" {
#include "tuple.h"
}


TEST_CASE( "Test tuple types", "[tuple]" )
{
    REQUIRE(1 == 1);
}
