/*
  Documentation: https://www.path.blog/docs/malloc.html
*/

#pragma once
#include "pathlib/types/types.h"

//---
#define MALLOC(A) ::Pathlib::Memory::malloc(A)
#define REALLOC(A, B) ::Pathlib::Memory::realloc(A, B)
#define FREE(A) ::Pathlib::Memory::free((void**)&A)

namespace Pathlib::Memory {

//---
Containers::SafePtr<u8> malloc(u64 size,
                               const utf8* name = nullptr);
Containers::SafePtr<u8> realloc(Containers::SafePtr<u8> ptr,
                                u64 size,
                                const utf8* name = nullptr);
void free(Containers::SafePtr<u8> ptr);
}