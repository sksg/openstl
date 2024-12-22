// #include <catch2/catch_test_macros.hpp>
// #include "catch2/matchers/catch_matchers_string.hpp"
#include <catch.hpp>
#include <openstl/vector.hpp>

#ifndef OPENSTL_TEST_CXX_VERSION
    #error These tests require the C++ version be defined (as a macro)
#endif

TEST_CASE((std::string("version:") + std::string(OPENSTL_TEST_CXX_VERSION)).c_str()) {
#ifdef _MSVC_LANG
    INFO("_MSVC_LANG = " << _MSVC_LANG);
#endif
#ifdef __cplusplus
    INFO("__cplusplus = " << __cplusplus);
#endif

    REQUIRE_THAT(OPENSTL_CXX_VERSION_STRING, Catch::Matchers::Equals(OPENSTL_TEST_CXX_VERSION));
}
