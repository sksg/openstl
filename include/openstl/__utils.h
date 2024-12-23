#pragma once

#define OPENSTL_STR(x) OPENSTL_STR_IMPL(x)
#define OPENSTL_STR_IMPL(x) #x

#define OPENSTL_IGNORE_UNUSED(x) (void)(x)

#define OPENSTL_CXX98_VERSION (199711L)
#define OPENSTL_CXX03_VERSION (OPENSTL_CXX98_VERSION)  // Cannot distinguish!!
#define OPENSTL_CXX11_VERSION (201103L)
#define OPENSTL_CXX14_VERSION (201402L)
#define OPENSTL_CXX17_VERSION (201703L)
#define OPENSTL_CXX20_VERSION (202002L)
#define OPENSTL_CXX23_VERSION (202302L)

/* Detect the current C++ version running in the compiler */
#if defined(_MSVC_LANG) && _MSVC_LANG >= OPENSTL_CXX98
    #define OPENSTL_CXX_VERSION (_MSVC_LANG)
#elif defined(__cplusplus) && __cplusplus >= OPENSTL_CXX98
    #define OPENSTL_CXX_VERSION (__cplusplus)
#endif

#if !defined(OPENSTL_CXX_VERSION) || (OPENSTL_CXX_VERSION < OPENSTL_CXX98)
    #error cannot determine the c++ version
#elif OPENSTL_CXX_VERSION >= OPENSTL_CXX23_VERSION
    #define OPENSTL_CXX98_SUPPORT
    #define OPENSTL_CXX03_SUPPORT
    #define OPENSTL_CXX11_SUPPORT
    #define OPENSTL_CXX14_SUPPORT
    #define OPENSTL_CXX17_SUPPORT
    #define OPENSTL_CXX20_SUPPORT
    #define OPENSTL_CXX23_SUPPORT
    #define OPENSTL_CXX23
    #define OPENSTL_CXX_VERSION_STRING ("C++23")
#elif OPENSTL_CXX_VERSION >= OPENSTL_CXX20_VERSION
    #define OPENSTL_CXX98_SUPPORT
    #define OPENSTL_CXX03_SUPPORT
    #define OPENSTL_CXX11_SUPPORT
    #define OPENSTL_CXX14_SUPPORT
    #define OPENSTL_CXX17_SUPPORT
    #define OPENSTL_CXX20_SUPPORT
    #define OPENSTL_CXX20
    #define OPENSTL_CXX_VERSION_STRING ("C++20")
#elif OPENSTL_CXX_VERSION >= OPENSTL_CXX17_VERSION
    #define OPENSTL_CXX98_SUPPORT
    #define OPENSTL_CXX03_SUPPORT
    #define OPENSTL_CXX11_SUPPORT
    #define OPENSTL_CXX14_SUPPORT
    #define OPENSTL_CXX17_SUPPORT
    #define OPENSTL_CXX17
    #define OPENSTL_CXX_VERSION_STRING ("C++17")
#elif OPENSTL_CXX_VERSION >= OPENSTL_CXX14_VERSION
    #define OPENSTL_CXX98_SUPPORT
    #define OPENSTL_CXX03_SUPPORT
    #define OPENSTL_CXX11_SUPPORT
    #define OPENSTL_CXX14_SUPPORT
    #define OPENSTL_CXX14
    #define OPENSTL_CXX_VERSION_STRING ("C++14")
#elif OPENSTL_CXX_VERSION >= OPENSTL_CXX11_VERSION
    #define OPENSTL_CXX98_SUPPORT
    #define OPENSTL_CXX03_SUPPORT
    #define OPENSTL_CXX11_SUPPORT
    #define OPENSTL_CXX11
    #define OPENSTL_CXX_VERSION_STRING ("C++11")
#elif OPENSTL_CXX_VERSION >= OPENSTL_CXX03_VERSION
    #define OPENSTL_CXX98_SUPPORT
    #define OPENSTL_CXX03_SUPPORT
    #define OPENSTL_CXX03
    #define OPENSTL_CXX_VERSION_STRING ("C++03")
#elif OPENSTL_CXX_VERSION >= OPENSTL_CXX98_VERSION
    #define OPENSTL_CXX98_SUPPORT
    #define OPENSTL_CXX98
    #define OPENSTL_CXX_VERSION_STRING ("C++98")
#else
    #pragma message "This version of C++ is not currently supported: " OPENSTL_STR(OPENSTL_CXX_VERSION)
    #error Unsupported C++ version
#endif

#undef STR

#ifdef OPENSTL_CXX11_SUPPORT
    #define OPENSTL_CONSTEXPR constexpr
    #define OPENSTL_NOEXCEPT(x) noexcept(x)
    #define OPENSTL_NOEXCEPT_NOEXCEPT(x) noexcept(noexcept(x))
#else
    #define OPENSTL_CONSTEXPR
    #define OPENSTL_NOEXCEPT(x)
    #define OPENSTL_NOEXCEPT_NOEXCEPT(x)
#endif

#ifdef OPENSTL_CXX11_SUPPORT
    #define OPENSTL_CONSTEXPR_SINCE_CXX11 OPENSTL_CONSTEXPR
    #define OPENSTL_NOEXCEPT_SINCE_CXX11(x) OPENSTL_NOEXCEPT(x)
    #define OPENSTL_NOEXCEPT_NOEXCEPT_SINCE_CXX11(x) OPENSTL_NOEXCEPT_NOEXCEPT(x)
#else
    #define OPENSTL_CONSTEXPR_SINCE_CXX11
    #define OPENSTL_NOEXCEPT_SINCE_CXX11(x)
    #define OPENSTL_NOEXCEPT_NOEXCEPT_SINCE_CXX11(x)
#endif

#ifdef OPENSTL_CXX14_SUPPORT
    #define OPENSTL_CONSTEXPR_SINCE_CXX14 OPENSTL_CONSTEXPR
    #define OPENSTL_NOEXCEPT_SINCE_CXX14(x) OPENSTL_NOEXCEPT(x)
    #define OPENSTL_NOEXCEPT_NOEXCEPT_SINCE_CXX14(x) OPENSTL_NOEXCEPT_NOEXCEPT(x)
#else
    #define OPENSTL_CONSTEXPR_SINCE_CXX14
    #define OPENSTL_NOEXCEPT_SINCE_CXX14(x)
    #define OPENSTL_NOEXCEPT_NOEXCEPT_SINCE_CXX14(x)
#endif

#ifdef OPENSTL_CXX17_SUPPORT
    #define OPENSTL_CONSTEXPR_SINCE_CXX17 OPENSTL_CONSTEXPR
    #define OPENSTL_NOEXCEPT_SINCE_CXX17(x) OPENSTL_NOEXCEPT(x)
    #define OPENSTL_NOEXCEPT_NOEXCEPT_SINCE_CXX17(x) OPENSTL_NOEXCEPT_NOEXCEPT(x)
#else
    #define OPENSTL_CONSTEXPR_SINCE_CXX17
    #define OPENSTL_NOEXCEPT_SINCE_CXX17(x)
    #define OPENSTL_NOEXCEPT_NOEXCEPT_SINCE_CXX17(x)
#endif

#ifdef OPENSTL_CXX20_SUPPORT
    #define OPENSTL_CONSTEXPR_SINCE_CXX20 OPENSTL_CONSTEXPR
    #define OPENSTL_NOEXCEPT_SINCE_CXX20(x) OPENSTL_NOEXCEPT(x)
    #define OPENSTL_NOEXCEPT_NOEXCEPT_SINCE_CXX20(x) OPENSTL_NOEXCEPT_NOEXCEPT(x)
#else
    #define OPENSTL_CONSTEXPR_SINCE_CXX20
    #define OPENSTL_NOEXCEPT_SINCE_CXX20(x)
    #define OPENSTL_NOEXCEPT_NOEXCEPT_SINCE_CXX20(x)
#endif

#ifdef OPENSTL_CXX23_SUPPORT
    #define OPENSTL_CONSTEXPR_SINCE_CXX23 OPENSTL_CONSTEXPR
    #define OPENSTL_NOEXCEPT_SINCE_CXX23(x) OPENSTL_NOEXCEPT(x)
    #define OPENSTL_NOEXCEPT_NOEXCEPT_SINCE_CXX23(x) OPENSTL_NOEXCEPT_NOEXCEPT(x)
#else
    #define OPENSTL_CONSTEXPR_SINCE_CXX23
    #define OPENSTL_NOEXCEPT_SINCE_CXX23(x)
    #define OPENSTL_NOEXCEPT_NOEXCEPT_SINCE_CXX23(x)
#endif
