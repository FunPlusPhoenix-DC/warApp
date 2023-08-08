#ifndef PCH_H

#define PCH_H

#include <Windows.h>

#endif

#ifdef WARAPPDLL_IMPORT

#define WARAPPDLL_API __declspec(dllimport)

#else

#define WARAPPDLL_API __declspec(dllexport)

#endif

extern DWORD dwErrorState;