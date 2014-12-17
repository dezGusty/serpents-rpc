##ProcessFactory


[TOC]



####enum Type
* **Blocking:** blocks other processes from executing if they use the same resource type.
* **NonBlocking:** does not block other processes(is not affected by Blocking type).
* **BlockAll:** blocks the execution of all other processes. 

####ExecuteProcessAndWait
  * **@IN: const std::string& process_to_execute** 
  path of the executable you want to execute.
  * **@IN int maximum_timeout_in_millis** 
  maximum time the process is allowed to run (pass -1 to run until the process finishes ) 
  * **@IN Type type** 
  The type of the process you want to start, defaults to NonBlocking
  * **@IN std::string resourceType**
 specifies the resource type you want to use. The application only takes this parameter in consideration if the type of the process is specified as *Blocking*.ResourceType defaults to empty string, this is not considered a process type by the application
  * ** @OUT std::shared_ptr<Process<int>>** Shared pointer containing an a Process object initialized with the return value. This value will be used to initialize the std::future type returned by the lambda.
~~~cpp
static std::shared_ptr<Process<int>> ExecuteProcessAndWait(
					const std::string& process_to_execute, 
					int maximum_timeout_in_millis,
					Type type = Type::NonBlocking,
					std::string resourceType = "");
~~~


####ExecuteProcessWithOutputCaptureAndWait

 * **@IN: const std::string& process_to_execute** 
   path of the executable you want to execute.
 * **@IN process_visible** Specifies whether the launched process is shown to the user or not  (if it has a GUI/console). 
* *NOTE:* value passes directly to the guslib function.
 * **@IN int maximum_timeout_in_millis** 
  maximum time the process is allowed to run (pass -1 to run until the process finishes )
 * **@IN int& output_code** Specifies whether the console output of the launched process needs to be captured.
* *NOTE:* value passed  directly to the guslib function. 
 * **@IN Type type** 
  The type of the process you want to start, defaults to NonBlocking
 * **@IN std::string resourceType**
 specifies the resource type you want to use. The application only takes this parameter in consideration if the type of the process is specified as *Blocking*.ResourceType defaults to empty string, this is not considered a process type by the application
 * ** @OUT std::shared_ptr<Process<int>>** Shared pointer containing an a Process object initialized with the return value. This value will be used to initialize the std::future type returned by the lambda.
~~~cpp
static std::shared_ptr<Process<std::string>> ExecuteProcessWithOutputCaptureAndWait(
					const std::string& process_to_execute,
					bool process_visible,
					bool retrieve_output,
					int maximum_timeout_in_millis,
					int& output_code,
					Type type = Type::NonBlocking,
					std::string resourceType = "");
~~~

####WaitForProcessTerminationByHandle

  * **@IN HANDLE process_handle**  Handle to the process.
  * **@IN int maximum_timeout_in_millis** 
  maximum time the process is allowed to run (pass -1 to run until the process finishes ) 
  * **@IN Type type** 
  The type of the process you want to start, defaults to NonBlocking
  * **@IN std::string resourceType**
 specifies the resource type you want to use. The application only takes this parameter in consideration if the type of the process is specified as *Blocking*.ResourceType defaults to empty string, this is not considered a process type by the application
  * ** @OUT std::shared_ptr<Process<void>>** Shared pointer containing an a Process object initialized with the return value. This value will be used to initialize the std::future type returned by the lambda.
~~~cpp
static std::shared_ptr<Process<void>> WaitForProcessTerminationByHandle(
					HANDLE process_handle, 
					int timeout_in_millis,
					Type type = Type::NonBlocking,
					std::string resourceType = "");
~~~

####ReadPipeContent

_Note:Because no timeout is specified for this method, the application defaults to -1 (infinite time)_

  * **@IN HANDLE process_handle** Handle to the process.
  * **@IN  bool keep_standard_output**
  * **@IN Type type** If set to TRUE, the pipe content will also be pushed to
      the standard output (console). If set to FALSE, the pipe content will be completely
      captured.
* *NOTE* value passed directly to the guslib method
  * **@IN std::string resourceType** The type of the process you want to start, defaults to NonBlocking
 specifies the resource type you want to use. The application only takes this parameter in consideration if the type of the process is specified as *Blocking*.ResourceType defaults to empty string, this is not considered a process type by the application
  * ** @OUT std::shared_ptr<Process<std::string>>** Shared pointer containing an a Process object initialized with the return value. This value will be used to initialize the std::future type returned by the lambda.
~~~cpp
static std::shared_ptr<Process<std::string>> ReadPipeContent(
					HANDLE process_handle, 
					bool keep_standard_output, 
					Type type = Type::NonBlocking, 
					std::string resourceType = "")
~~~

####Process Class
The Process class stores variables useful for the creation and management of processes. 
Its main function is to store the std::promise and std::function variables. 
* The std::promise represents the eventual value returned by the process 
*  std::function stores the method that will start the process.