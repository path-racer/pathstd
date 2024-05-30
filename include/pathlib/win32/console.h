﻿/*
  Documentation: https://www.path.blog/docs/console.html
*/

#pragma once
#include "pathlib/win32/safe_win32.h"
#include "pathlib/types/types.h"
#include "pathlib/error/error.h"
#include "pathlib/types/string/short_string.h"
#include "pathlib/types/string/long_string.h"
#include "pathlib/types/string/short_string_unsafe.h"
#include "pathlib/types/string/long_string_unsafe.h"

namespace Pathlib::_Internal {
  
//---
struct Console
{
  //---
  LongStringUnsafe<256> _buffer;

  //---
  inline bool set_text_attributes(u16 attributes)
  {
    return Win32::set_console_text_attributes(attributes);
  }

  //---
  template <u64 CAPACITY>
  inline bool write(const ShortString<CAPACITY>& string)
  {
    return Win32::write_console(string.str, string.size) && 
           Win32::write_console(u8"\n", 1);
  }

  //---
  template <u64 CAPACITY>
  inline bool write(const ShortStringUnsafe<CAPACITY>& string)
  {
    return Win32::write_console(string.str, string.size) && Win32::write_console(u8"\n", 1);
  }

  //---
  template <u64 RESERVE_CAPACITY>
  inline bool write(const LongString<RESERVE_CAPACITY>& string)
  {
    return Win32::write_console(string.str, string.size) &&
           Win32::write_console(u8"\n", 1);
  }

  //---
  template <u64 RESERVE_CAPACITY>
  inline bool write(const LongStringUnsafe<RESERVE_CAPACITY>& string)
  {
    return Win32::write_console(string.str, string.size) && Win32::write_console(u8"\n", 1);
  }

  //---
  inline bool write(const utf8* string)
  {
    return Win32::write_console(string, String::size_of(string)) && Win32::write_console(u8"\n", 1);
  }

  //---
  template <typename... Args>
  inline bool write(Args&&... args)
  {
    _buffer.size = 0;
    (_buffer._append(_buffer, args), ...);
    _buffer.append(u8'\n');
    return Win32::write_console(_buffer.str, _buffer.size);
  }
};
}

//---
namespace Pathlib { extern _Internal::Console console; }