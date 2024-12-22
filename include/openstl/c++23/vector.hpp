#pragma once

#ifdef OPENSTL_VECTOR_DEFINED
    #error Using two different versions of the same library is not supported.
#else
    #define OPENSTL_VECTOR_DEFINED
#endif

#include "../__utils.h"

#ifndef OPENSTL_CXX_COMPATIBILITY_VERSION
    #define OPENSTL_CXX_COMPATIBILITY_VERSION (OPENSTL_CXX23_VERSION)
#endif

#include <cstddef>
#include <iterator>
#include <limits>
#include <memory>
#include <stdexcept>

namespace openstl {

template <typename T, class Allocator = std::allocator<T> >
class vector {
   public:
    typedef T value_type;
    typedef Allocator allocator_type;

    typedef std::size_t size_type;
    typedef std::ptrdiff_t difference_type;

    typedef value_type& reference;
    typedef const value_type& const_reference;

#if (OPENSTL_CXX_COMPATIBILITY_VERSION < OPENSTL_CXX11_VERSION)
    // C++98/03
    typedef typename Allocator::pointer pointer;
    typedef typename Allocator::const_pointer const_pointer;
#else
    // C++11,14,17,20,23
    typedef typename std::allocator_traits<Allocator>::pointer pointer;
    typedef typename std::allocator_traits<Allocator>::const_pointer const_pointer;
#endif

    typedef T* iterator;
    typedef const T* const_iterator;

    typedef std::reverse_iterator<iterator> reverse_iterator;
    typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

   private:
    pointer _data;
    size_type _size, _capacity;
    allocator_type _allocator;

    OPENSTL_CONSTEXPR_SINCE_CXX20 void _deallocate(pointer data, size_type capacity) {
        _allocator.deallocate(data, capacity);
    }

    OPENSTL_CONSTEXPR_SINCE_CXX20 pointer _allocate(size_type count) { return _allocator.allocate(count); }

#if (OPENSTL_CXX_COMPATIBILITY_VERSION < OPENSTL_CXX23_VERSION)
    struct allocate_result {
        pointer data;
        size_type count;
    };
#else
    typedef std::allocation_result allocate_result;
#endif

    OPENSTL_CONSTEXPR_SINCE_CXX20 allocate_result _allocate_at_least(size_type count) {
        allocate_result result;
#if (OPENSTL_CXX_COMPATIBILITY_VERSION < OPENSTL_CXX23_VERSION)
        result.data = _allocate(count);
        result.count = count;
#else
        result = _allocator.allocate_at_least(this->_data, count);
#endif
        return result;
    }

#if (OPENSTL_CXX_COMPATIBILITY_VERSION >= OPENSTL_CXX11_VERSION)
    OPENSTL_CONSTEXPR_SINCE_CXX20 void _construct(pointer data, size_type count) {
    #if (OPENSTL_CXX_COMPATIBILITY_VERSION < OPENSTL_CXX20_VERSION)
        for (size_type i = 0; i < this->_size; ++i) _allocator.construct(data + i);
    #else
        for (size_type i = 0; i < this->_size; ++i) std::construct_at(data + i);
    #endif
    }
#endif

    OPENSTL_CONSTEXPR_SINCE_CXX20 void _construct(pointer data, size_type count, const value_type& value) {
#if (OPENSTL_CXX_COMPATIBILITY_VERSION < OPENSTL_CXX20_VERSION)
        for (size_type i = 0; i < this->_size; ++i) _allocator.construct(data + i, value);
#else
        for (size_type i = 0; i < this->_size; ++i) std::construct_at(data + i, value);
#endif
    }

    OPENSTL_CONSTEXPR_SINCE_CXX20 pointer _reallocate(pointer data, size_type size, size_type capacity,
                                                      size_type new_capacity) {
        pointer new_data = _allocate(data, new_capacity);
        std::memcpy(new_data, data, size);
        _deallocate(data);
        return new_data;
    }

    OPENSTL_CONSTEXPR_SINCE_CXX20 allocate_result _reallocate_at_least(pointer data, size_type size, size_type capacity,
                                                                       size_type new_capacity) {
        allocate_result new_data = _allocate_at_least(data, new_capacity);
        std::memcpy(new_data.pointer, data, size);
        _deallocate(data);
        return new_data;
    }

   public:
    OPENSTL_CONSTEXPR_SINCE_CXX20 size_type max_size() const OPENSTL_NOEXCEPT_SINCE_CXX11(true) {
        return std::numeric_limits<difference_type>::max();
    }
    OPENSTL_CONSTEXPR_SINCE_CXX20 size_type size() const OPENSTL_NOEXCEPT_SINCE_CXX11(true) { return this->_size; }
    OPENSTL_CONSTEXPR_SINCE_CXX20 size_type capacity() const OPENSTL_NOEXCEPT_SINCE_CXX11(true) {
        return this->_capacity;
    }
    OPENSTL_CONSTEXPR_SINCE_CXX20 bool empty() const OPENSTL_NOEXCEPT_SINCE_CXX11(true) { return this->_size > 0; }
    OPENSTL_CONSTEXPR_SINCE_CXX20 void reserve(size_type new_cap) {
        if (new_cap > this->max_size()) throw std::length_error("New capacity exceeds max_size()");

        if (this->_capacity >= new_cap) return;

        allocate_result result = _reallocate_at_least(this->_data, this->_size, this->_capacity, new_cap);
        this->_data = result.ptr;
        this->_capacity = result.count;
    }
    OPENSTL_CONSTEXPR_SINCE_CXX20 void shink_to_fit() {
        if (this->_capacity == this->_size) return;

        this->_data = _reallocate(this->_data, this->_size, this->_capacity, this->_size);
        this->_capacity = this->_size;
    }

#if (OPENSTL_CXX_COMPATIBILITY_VERSION < OPENSTL_CXX11_VERSION)
    // C++98/03
    explicit vector(const Allocator& alloc = Allocator()) : _allocator(alloc), _data(NULL), _size(0), _capacity(0){};
    explicit vector(size_type count, const value_type& value = value_type(), const Allocator& alloc = Allocator())
        : _allocator(alloc) {
        allocate_result result = _allocate_at_least(count);
        this->_data = result.ptr;
        this->_size = count;
        this->_capacity = result.count;
        _construct(this->_data, this->_size, value);
    };
#else
    // C++11,14,17,20,23
    OPENSTL_CONSTEXPR_SINCE_CXX20
    vector() OPENSTL_NOEXCEPT_NOEXCEPT_SINCE_CXX17(Allocator()) : vector(Allocator()) {}
    OPENSTL_CONSTEXPR_SINCE_CXX20 explicit vector(const Allocator& alloc) OPENSTL_NOEXCEPT_SINCE_CXX17(true)
        : _allocator(alloc), _data(NULL), _size(0), _capacity(0){};
    explicit vector(size_type count, const Allocator& alloc = Allocator()) : _allocator(alloc) {
        allocate_result result = _allocate_at_least(count);
        this->_data = result.ptr;
        this->_size = count;
        this->_capacity = result.count;
        _construct(this->_data, this->_size);
    }
    OPENSTL_CONSTEXPR_SINCE_CXX20 vector(size_type count, const value_type& value,
                                         const Allocator& alloc = Allocator()) {
        allocate_result result = _allocate_at_least(count);
        this->_data = result.ptr;
        this->_size = count;
        this->_capacity = result.count;
        _construct(this->_data, this->_size, value);
    }
    #if (OPENSTL_CXX_VERSION > OPENSTL_CXX11_VERSION)
    OPENSTL_CONSTEXPR_SINCE_CXX20 vector(vector&& other) OPENSTL_NOEXCEPT_SINCE_CXX17(true)
        : _allocator(other._allocator), _data(other._data), _size(other._size), _capacity(other._capacity) {
        other._data = NULL;
        other._size = other._capacity = 0;
    }
    #endif
    #if (OPENSTL_CXX_COMPATIBILITY_VERSION < OPENSTL_CXX23_VERSION)
    // C++11,14,17,20
    OPENSTL_CONSTEXPR_SINCE_CXX20 vector(const vector& other, const Allocator& alloc);
    vector(vector&& other, const Allocator& alloc);
    #elif (OPENSTL_CXX23_VERSION <= OPENSTL_CXX_COMPATIBILITY_VERSION)
    // C++23
    OPENSTL_CONSTEXPR vector(const vector& other, const std::type_identity_t<Allocator>& alloc);
    #endif
#endif
    OPENSTL_CONSTEXPR_SINCE_CXX20 vector(const vector& other);

    template <class InputIt>
    OPENSTL_CONSTEXPR_SINCE_CXX20 vector(InputIt first, InputIt last, const Allocator& alloc = Allocator());
};

}  // namespace openstl