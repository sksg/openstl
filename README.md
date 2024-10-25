# Open Standard Template Library (OpenSTL) 

This library is an open source implementation of the Standard Template library for C++.

You can use this library for:

- Use an STL version newer than your compiler supports
  - For example, use a C++23 complient std::expected available in C++20 or earlier
- Replace your compilers STL with a compiler-agnostic STL
- Use this STL in your own C++ compiler
- As a thrid-party reference
- Use the included unit-tests and benchmarks for testing and validation

# Structure of the library

- `root`
  - `include`
    - `openstl`  # Uses the namespace `openstl::`
      - `vector.hpp`  # the `<openstl/vector.hpp>` is equivalent to `<vector>`
      - ...
      - `c++11`  # the <openstl/c++11/...> is equivalent to <...> with `--std=c++11`
        - `vector.hpp`
      - ...
    - `std`  # includes `openstl::` from above under the `std::` namespace
      - `vector`  # drop-in replacement for `<vector>`
      - ...

# Instructions for use

We do not have our first working implementation. So usage is at your own descretion at the moment.

# How can you support?

What we really need right now are more contributors and contributions. Please consider contributing by using pull requests. 

We are also looking for more maintainers. If you want to be a maintainer, let me know.

You can also [support me personally](https://github.com/sponsors/sksg), thus indirectly supporting this library in particular.