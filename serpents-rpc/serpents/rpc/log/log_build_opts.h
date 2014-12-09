#pragma once

// Add platform specific definitions.
#include "guslib/guslib_platform.h"

#ifdef SERVERMGR_EXP
#define SERVERMGR_EXPORT_SYMBOL __declspec (dllexport)
#define SERVERMGR_EXPIMP_TEMPLATE
#else
#ifdef SERVERMGR_STANDALONE
#define SERVERMGR_EXPORT_SYMBOL 
#define SERVERMGR_EXPIMP_TEMPLATE 
#else
#define SERVERMGR_EXPORT_SYMBOL __declspec (dllimport)
#define SERVERMGR_EXPIMP_TEMPLATE extern
#endif
#endif // SERVERMGR_EXP

#ifdef SERVERMGR_EXP
#define EXP_STATIC_VAR extern "C" __declspec(dllexport)
#else
#define EXP_STATIC_VAR extern "C" __declspec(dllimport)
#endif

