#ifndef BASE_H
#define BASE_H
#pragma once


#ifdef SERPENTSRPC_EXPORTS
#define SERPENTSDLL __declspec (dllexport)
#else
#define SERPENTSDLL __declspec (dllimport)

#endif

#ifdef USEEASYLOGGING
//#include "easylogging++.h"
#endif

#endif
