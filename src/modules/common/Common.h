#pragma once

#include <SDL.h>
#include <SDL_assert.h>
#include "Compiler.h"
#include <memory>
#include <stdarg.h>

#ifdef _MSC_VER
#define __PRETTY_FUNCTION__ __FUNCSIG__
#endif

void cp_snprintf(char* dest, size_t size, const char* fmt, ...) __attribute__((format(__printf__, 3, 4)));
inline void cp_snprintf(char* dest, size_t size, const char* fmt, ...) {
	va_list ap;
	va_start(ap, fmt);
	SDL_vsnprintf(dest, size, fmt, ap);
	va_end(ap);
}

template<class T, class S>
inline T assert_cast(const S object) {
#ifdef __cpp_rtti
	SDL_assert(dynamic_cast<T>(object) == static_cast<T>(object));
#endif
	return static_cast<T>(object);
}
