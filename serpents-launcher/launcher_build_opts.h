#pragma once

// Add platform specific definitions.
#include "guslib/guslib_platform.h"

#ifdef LAUNCHER_EXP
#define LAUNCHER_EXPORT_SYMBOL __declspec (dllexport)
#define LAUNCHER_EXPIMP_TEMPLATE
#else
#ifdef LAUNCHER_STANDALONE
#define LAUNCHER_EXPORT_SYMBOL 
#define LAUNCHER_EXPIMP_TEMPLATE 
#else
#define LAUNCHER_EXPORT_SYMBOL __declspec (dllimport)
#define LAUNCHER_EXPIMP_TEMPLATE extern
#endif
#endif // LAUNCHER_EXP

#ifdef S
LAUNCHER__EXP
#define EXP_STATIC_VAR extern "C" __declspec(dllexport)
#else
#define EXP_STATIC_VAR extern "C" __declspec(dllimport)
#endif



