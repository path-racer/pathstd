/*
  Documentation: https://www.path.blog/docs/vector.html
*/

#pragma once
#include "pathlib/types/types.h"
#include "pathlib/memory/memcpy.h"

namespace Pathlib {

//---
template <typename T, 
          u64 RESERVE_CAPACITY>
struct Vector
{
private:
  //---
  T* _data;
  u64 _count;
  u64 _capacity;

public:
  //---
  Vector(const MemoryName& name,
         u64 reserve_capacity = RESERVE_CAPACITY)
  {
    _capacity = reserve_capacity;
    _data = (T*)malloc_unsafe(sizeof(T) * reserve_capacity,
                              FixedStringUnsafe<64>(u8"\"", name(), u8"\"::_data")._str);
    clear();
  }

  //---
  DISALLOW_COPY(Vector);

  //---
  ~Vector()
  {
    if (_data) {
      for (u64 c = 0; c < _count; ++c) {
        call_destructor<T>(&_data[c]);
      }
      free_unsafe((void**)&_data);
    }
  }

  //---
  inline T& operator[](u64 index)
  {
    if (EXPECT(index < _count)) {
      return _data[index];
    } else {
      get_errors().fatal(u8"Out of bounds access to Vector.");
      return _data[0];
    }
  }

  //---
  inline const T& operator[](u64 index) const
  {
    if (EXPECT(index < _count)) {
      return _data[index];
    } else {
      get_errors().fatal(u8"Out of bounds access to Vector.");
      return _data[0];
    }
  }

  //---
  template <typename... Args>
  inline SafePtr<T> emplace_back(u64 count = 1,
                                 Args&&... constructor_args)
  {
    if (EXPECT((_count + count) > _count)) {
      u64 original_count = _count;
      _count += count;
      if (_count > _capacity) {
        _capacity = _count * 1.5;
        _data = (T*)realloc_unsafe(_data, sizeof(T) * _capacity);
      }
      call_constructor<T>(_data + original_count, constructor_args...);
      return SafePtr<T>(_data + original_count, 1);
    } else {
      get_errors().fatal(u8"Failed to emplace_back() Vector; it is already at capacity.");
      return SafePtr<T>(nullptr, 0);
    }
  }

  //---
  inline void remove(u64 index)
  {
    if (EXPECT(index < _count)) {
      call_destructor<T>(&_data[index]);
      --_count;
      memcpy_unsafe(index, _data + _count, sizeof(T));
    } else {
      get_errors().fatal(u8"Failed to remove() from Vector; index is out of bounds.");
    }
  }

  //---
  inline void remove(u64 index,
                     u64 count)
  {
    if (EXPECT(((index + count) > index) &&
               ((index + count) <= _count))) {
      for (u64 c = index; c < count; ++c) {
        call_destructor<T>(&_data[c]);
      }
      T* start = (_data + index);
      T* end = (_data + _count - count);
      _count -= count;
      memcpy_unsafe(start, end, sizeof(T) * count);
    } else {
      get_errors().fatal(u8"Failed to remove() from Vector; removal is out of bounds.");
    }
  }

  //---
  inline void clear()
  {
    _count = 0;
  }

  //---
  inline u64 get_count()
  {
    return _count;
  }
};
}