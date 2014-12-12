#ifndef LAUNCHER_PROCESS_UTIL_H_
#define LAUNCHER_PROCESS_UTIL_H_

#include <string>
#include <cstdio>
#include <windows.h>
#include <tlhelp32.h>
#include <comdef.h>

#include "launcher_build_opts.h"

namespace serpents{
  namespace launcher{
    class LAUNCHER_EXPORT_SYMBOL ProcessUtil{
    public:
      // @in process path
      // tries to get the name of the process from the path 
      // calls closeProcessByHandle after finding the corresponding handle
      static void closeProcessByName(const std::string processPath);

      // @in process handle
      // if a processs exists this method closes it 
      // NOTE: ExitProcess() detaches the process, TerminateProcess kills the process 
      static void closeProcessByHandle(HANDLE& Handle);
    };
  }
}

#endif LAUNCHER_PROCESS_UTIL_H_