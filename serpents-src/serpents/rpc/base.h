#ifndef BASE_H_
#define BASE_H_
#pragma once
//#pragma warning(disable:4251)

#ifdef SERPENTSRPC_EXPORTS
#define SERPENTSDLL __declspec (dllexport)
#else
#define SERPENTSDLL __declspec (dllimport)

#endif


#endif  // BASE_H_