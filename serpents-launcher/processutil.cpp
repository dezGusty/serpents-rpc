#include "processutil.h"
#include <iostream>
namespace serpents{
  namespace launcher{
    // @in process name
    void ProcessUtil::closeProcessByName(const std::string processPath){
      {
        std::string key("\\");
        size_t pos = processPath.rfind(key);
        std::string processName;
        if (pos < processPath.length()){
          processName = processPath.substr(pos + 1, processPath.length());
        }
        else{
          processName = processPath;
        }
        PROCESSENTRY32 entry;
        entry.dwSize = sizeof(PROCESSENTRY32);

        HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);

        if (Process32First(snapshot, &entry) == TRUE)
        {
          while (Process32Next(snapshot, &entry) == TRUE)
          {
            _bstr_t buff(entry.szExeFile);
            const char* entry_char = buff;
            if (strcmp(entry_char, processName.c_str()) == 0)
            {
              HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, entry.th32ProcessID);
              closeProcessByHandle(hProcess);
            }
          }
        }

        CloseHandle(snapshot);
      }
    }

    void ProcessUtil::closeProcessByHandle(HANDLE& Handle){
      DWORD exitCode;
      if (GetExitCodeProcess(Handle, &exitCode)){
        TerminateProcess(Handle, exitCode);
      }
      CloseHandle(Handle);
    }

  }
}