#pragma once

// Add platform specific definitions.
#include "guslib/guslib_platform.h"

#ifdef XMLRPC_CPP_EXP
#define XMLRPC_CPP_EXPORT_SYMBOL __declspec (dllexport)
#define XMLRPC_CPP_EXPIMP_TEMPLATE
#else
#ifdef  XMLRPC_CPP_STANDALONE
#define XMLRPC_CPP_EXPORT_SYMBOL 
#define XMLRPC_CPP_EXPIMP_TEMPLATE 
#else
#define XMLRPC_CPP_EXPORT_SYMBOL __declspec (dllimport)
#define XMLRPC_CPP_EXPIMP_TEMPLATE extern
#endif
#endif // PLUGINLOGGERA_EXP
