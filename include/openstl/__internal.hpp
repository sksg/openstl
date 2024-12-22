#pragma once

#include <new>

#include "__utils.h"

namespace openstl {
namespace __internal {

template <typename T, typename S>
OPENSTL_CONSTEXPR_SINCE_CXX20 T* allocate(S count) {
    return static_cast<T*>(::operator new(sizeof(T) * count));
}

template <typename T>
OPENSTL_CONSTEXPR_SINCE_CXX20 void deallocate(T* memory_location) {
    ::operator delete(memory_location);
}
template <typename T>
OPENSTL_CONSTEXPR_SINCE_CXX20 void construct(T* memory_location) {
    ::new (static_cast<void*>(memory_location)) T();
}

template <typename T, typename S>
OPENSTL_CONSTEXPR_SINCE_CXX20 void construct(T* data, S count) {
    for (S i = 0; i < count; ++i) construct(data + i);
}

template <typename S>
OPENSTL_CONSTEXPR_SINCE_CXX20 void copy_memory(void* source, void* destination, S count) {
    std::memcpy(destination, source, count);
}

template <typename T, typename S>
OPENSTL_CONSTEXPR_SINCE_CXX20 T* reallocate(T* data, S used_count, S capcity, S new_capacity) {
    T* new_data = allocate(data, new_capacity);
    copy_memory(data, new_data, used_count);
    deallocate(data);
    return new_data;
}

}  // namespace __internal
}  // namespace openstl