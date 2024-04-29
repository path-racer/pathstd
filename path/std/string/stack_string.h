/* 'std/string/string.h'

  + Stack-allocated and bound to CAPACITY length.
  + Utilizes AVX for fast comparisons and copies.

    Path game engine: https://www.path.blog
*/

#pragma once
#include <string>
#include "../memory/avx_memcpy.h"
#include "../string/avx_strlen.h"
#include "../types.h"

namespace Path::Std::String {

/**/
template <u64 CAPACITY>
struct StackString
{
  static_assert(Math::is_multiple(CAPACITY, 32LLU), "Stack string capacity must be a multiple of 32 (AVX-width).");
  static_assert(CAPACITY <= 256, "Stack string capacity must be less than or equal to 256.");

  /**/
  alignas(32) char str[CAPACITY];
  char scratch[32];
  u32 length;
  
  /**/
  StackString()
  {
    clear();
  }
  ~StackString() {}
  
  /**/
  StackString(const char* string)
  {
    length = avx_strlen<CAPACITY, true>(string);
    avx_memcpy<true, false>(str, string, length + 1);
  }

  /**/
  inline void clear()
  {
    str[0] = '\0';
    length = 0;
  }
};
}