#ifndef PROCESSRUNNER_H_
#define PROCESSRUNNER_H_

//   This file is part of the serpents-rpc library, licensed under the terms of the MIT License.
//
//   The MIT License
//   Copyright (C) 2010-2014  The serpents-rpc team (See AUTHORS file)
//
//   Permission is hereby granted, free of charge, to any person obtaining a copy
//   of this software and associated documentation files (the "Software"), to deal
//   in the Software without restriction, including without limitation the rights
//   to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//   copies of the Software, and to permit persons to whom the Software is
//   furnished to do so, subject to the following conditions:
//
//   The above copyright notice and this permission notice shall be included in
//   all copies or substantial portions of the Software.
//
//   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//   OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
//   THE SOFTWARE.

#include <windows.h>
#include <string>
#include <sstream>
#include "serpents/rpc/base.h"
#include <vector>
namespace serpents{
  namespace procrun{
    int SERPENTSDLL ExecuteProcessAndWait(const std::string& process_to_execute, int maximum_timeout_in_millis);
    std::string SERPENTSDLL ExecuteProcessWithOutputCaptureAndWaitWindows(
      const std::string& process_to_execute,
      bool process_visible,
      bool retrieve_output,
      int maximum_timeout_in_millis,
      int& output_code);

    std::string SERPENTSDLL ExecuteProcessWithOutputCaptureAndWait(
      const std::string& process_to_execute,
      bool process_visible,
      bool retrieve_output,
      int maximum_timeout_in_millis,
      int& output_code);

    void SERPENTSDLL  WaitForProcessTerminationByHandle(HANDLE process_handle, int timeout_in_millis);

    int  SERPENTSDLL GetProcessReturnCode(HANDLE process_handle);

    std::string  SERPENTSDLL ReadPipeContent(HANDLE process_handle, bool keep_standard_output);

    std::string  SERPENTSDLL GetLocalHostName();
  }
}

#endif // PROCESSRUNNER_H_