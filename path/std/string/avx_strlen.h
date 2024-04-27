/* 'std/string/avx_strlen.h'

  + Utilizes AVX2 to read length of string.
  + Protected against bad page boundary crossing.
  + To check 128 bytes per iteration, we first read previous 128-byte aligned address and mask out unused bits.

    Path game engine: https://www.path.blog
*/

#pragma once
#include "../types.h"
#include "../math/math.h"

namespace Path::Std::String {

/**/
static inline u64 avx_strlen(const char* str) 
{
  I8 zero = I8_SETZERO();
  u64 counted = 0;
  const char* _s = Math::align_previous<128>(str);
  i64 ignore_bytes = str - _s;
  if (ignore_bytes < 64) {
    u64 check32 = (u32)I8_MOVEMASK(I8_CMP_EQ8(I8_LOAD((I8*)(_s)), zero));
    u64 check64 = (u32)I8_MOVEMASK(I8_CMP_EQ8(I8_LOAD((I8*)(_s + 32)), zero));
    u64 zero_mask64 = (check32 | (check64 << 32)) &
                      (UINT64_MAX << ignore_bytes);
    if (zero_mask64) {
      return Math::first_bit_set(zero_mask64) - ignore_bytes;
    }
  }
  u64 check96 = (u32)I8_MOVEMASK(I8_CMP_EQ8(I8_LOAD((I8*)(_s + 64)), zero));
  u64 check128 = (u32)I8_MOVEMASK(I8_CMP_EQ8(I8_LOAD((I8*)(_s + 96)), zero));
  u64 zero_mask128 = (check96 | (check128 << 32)) &
                     (UINT64_MAX << Math::max(0LL, ignore_bytes - 64LL));
  if (zero_mask128) {
    return (64 - ignore_bytes + Math::first_bit_set(zero_mask128));
  }
  counted += 128 - ignore_bytes;
  str = _s + 128;
  while (true) {
    u64 check32 = (u32)I8_MOVEMASK(I8_CMP_EQ8(I8_LOAD((I8*)(str)), zero));
    u64 check64 = (u32)I8_MOVEMASK(I8_CMP_EQ8(I8_LOAD((I8*)(str + 32)), zero));
    u64 zero_mask64 = (check32 | (check64 << 32));
    if (zero_mask64) {
      return (counted + Math::first_bit_set(zero_mask64));
    }
    u64 check96 = (u32)I8_MOVEMASK(I8_CMP_EQ8(I8_LOAD((I8*)(str + 64)), zero));
    u64 check128 = (u32)I8_MOVEMASK(I8_CMP_EQ8(I8_LOAD((I8*)(str + 96)), zero));
    u64 zero_mask128 = (check96 | (check128 << 32));
    if (zero_mask128) {
      return (counted + 64 + Math::first_bit_set(zero_mask128));
    }
    counted += 128;
    str += 128;
  }
  return 0;
}
}