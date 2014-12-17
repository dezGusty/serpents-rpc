##ProcessUtil

[TOC]

####closeProcessByName
_ The method tries to extract the name of the process from the path in order to obtain the process Handle. Calls closeProcessByHandle after finding the corresponding Handle._
* **@IN processPath** the path of the executable.
~~~cpp
	static void closeProcessByName(const std::string processPath);
~~~

####closeProcessByHandle
 _If a processs exists this method closes it_
 * **@IN: HANDLE& Handle** process to close
 * *NOTE:* ExitProcess() detaches the process, TerminateProcess() kills the process 
~~~cpp
	static void closeProcessByHandle(HANDLE& Handle);
~~~