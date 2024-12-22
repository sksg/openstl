#pragma once

#include "__utils.h"

// Include the version corresponding the chosen C++ standard in the compiler
#if defined(OPENSTL_CXX03)
    #include "c++03/vector.hpp"
#elif defined(OPENSTL_CXX11)
    #include "c++11/vector.hpp"
#elif defined(OPENSTL_CXX14)
    #include "c++14/vector.hpp"
#elif defined(OPENSTL_CXX17)
    #include "c++17/vector.hpp"
#elif defined(OPENSTL_CXX20)
    #include "c++20/vector.hpp"
#elif defined(OPENSTL_CXX23)
    #include "c++23/vector.hpp"
#endif

#if !defined(OPENSTL_VECTOR_DEFINED) || !defined(OPENSTL_CXX_COMPATIBILITY_VERSION)
    #error Library error: no versions of openstl::vector was found
#endif
