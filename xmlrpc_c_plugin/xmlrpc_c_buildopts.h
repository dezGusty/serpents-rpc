#pragma once

//  Add platform specific definitions.
#include "guslib/guslib_platform.h"

#ifdef PLUGINXMLRPC_C_EXP
#define PLUGINXMLRPC_C_EXPORT_SYMBOL __declspec (dllexport)
#define PLUGINXMLRPC_C_EXPIMP_TEMPLATE
#else
#ifdef PLUGINXMLRPC_C_STANDALONE
#define PLUGINXMLRPC_C_EXPORT_SYMBOL 
#define PLUGINXMLRPC_C_EXPIMP_TEMPLATE 
#else
#define PLUGINXMLRPC_C_EXPORT_SYMBOL __declspec (dllimport)
#define PLUGINXMLRPC_C_EXPIMP_TEMPLATE extern
#endif
#endif // PLUGINLOGGERA_EXP
