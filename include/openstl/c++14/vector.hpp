#pragma once

#ifndef OPENSTL_CXX_COMPATIBILITY_VERSION
    #define OPENSTL_CXX_COMPATIBILITY_VERSION (OPENSTL_CXX14_VERSION)
#endif

#include "../c++23/vector.hpp"

#if !defined(OPENSTL_VECTOR_DEFINED)
    #error Library error: no versions of openstl::vector was found
#endif