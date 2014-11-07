#pragma once

// Add platform specific definitions.
#include "guslib/guslib_platform.h"

#ifdef SSLSERVER_EXP
#define SSLSERVER_EXPORT_SYMBOL __declspec (dllexport)
#define SSLSERVER_EXPIMP_TEMPLATE
#else
#ifdef SSLSERVER_STANDALONE
#define SSLSERVER_EXPORT_SYMBOL 
#define SSLSERVER_EXPIMP_TEMPLATE 
#else
#define SSLSERVER_EXPORT_SYMBOL __declspec (dllimport)
#define SSLSERVER_EXPIMP_TEMPLATE extern
#endif
#endif // SSLSERVER_EXP

#ifdef SSLSERVER_EXP
#define SSLEXP_STATIC_VAR extern "C" __declspec(dllexport)
#else
#define SSLEXP_STATIC_VAR extern "C" __declspec(dllimport)
#endif

