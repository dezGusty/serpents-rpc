#pragma once
#ifndef ANY_H
#define ANY_H

#include <string>
#include "base.h"

#ifdef SERPENTSRPC_EXPORTS
#define ANY_DLL _declspec(dllexport)
#else
#define ANY_DLL _declspec(dllimport)
#endif


#endif 