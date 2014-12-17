[block:api-header]
{
  "type": "fn",
  "title": "ExecuteProcessAndWait"
}
[/block]

[block:code]
{
  "codes": [
    {
      "code": "  static std::shared_ptr<Process<int>> ExecuteProcessAndWait(\n    const std::string& process_to_execute, \n    int maximum_timeout_in_millis,\n    Type type = Type::NonBlocking,\n    std::string resourceType = \"\");",
      "language": "cplusplus",
      "name": "ExecuteProcessAndWait"
    }
  ]
}
[/block]
  * **@IN: const std::string& process_to_execute** 
   path of the executable you want to execute.
  * **@IN int maximum_timeout_in_millis** 
  maximum time the process is allowed to run (pass -1 to run until the process finishes ) 
  * **@IN Type type** 
  The type of the process you want to start, defaults to NonBlocking
  * **@IN std::string resourceType**
 specifies the resource type you want to use. The application only takes this parameter in consideration if the type of the process is specified as *Blocking*.ResourceType defaults to empty string, this is not considered a process type by the application
  * ** @OUT std::shared_ptr<Process<int>>** Shared pointer containing an a Process object initialized with the return value. This value will be used to initialize the std::future type returned by the lambda.
[block:api-header]
{
  "type": "fn",
  "title": "ExecuteProcessWithOutputCaptureAndWait"
}
[/block]

[block:code]
{
  "codes": [
    {
      "code": "static std::shared_ptr<Process<std::string>> ExecuteProcessWithOutputCaptureAndWait(\n  \t\t\tconst std::string& process_to_execute,\n        bool process_visible,\n        bool retrieve_output,\n        int maximum_timeout_in_millis,\n        int& output_code,\n        Type type = Type::NonBlocking,\n\t\t\t\tstd::string resourceType = \"\");",
      "language": "cplusplus",
      "name": "ExecuteProcessWithOutputCaptureAndWait"
    }
  ]
}
[/block]
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
[block:api-header]
{
  "type": "fn",
  "title": "WaitForProcessTerminationByHandle"
}
[/block]

[block:code]
{
  "codes": [
    {
      "code": "static std::shared_ptr<Process<void>> WaitForProcessTerminationByHandle(\n\t\tHANDLE process_handle, \n    int timeout_in_millis,\n    Type type = Type::NonBlocking,\n    std::string resourceType = \"\");",
      "language": "cplusplus",
      "name": "WaitForProcessTerminationByHandle"
    }
  ]
}
[/block]
  * **@IN HANDLE process_handle**  Handle to the process.
  * **@IN int maximum_timeout_in_millis** 
  maximum time the process is allowed to run (pass -1 to run until the process finishes ) 
  * **@IN Type type** 
  The type of the process you want to start, defaults to NonBlocking
  * **@IN std::string resourceType**
 specifies the resource type you want to use. The application only takes this parameter in consideration if the type of the process is specified as *Blocking*.ResourceType defaults to empty string, this is not considered a process type by the application
[block:api-header]
{
  "type": "fn",
  "title": "ReadPipeContent"
}
[/block]
Because no timeout is specified for this method, the application defaults to -1 (infinite time)
[block:code]
{
  "codes": [
    {
      "code": " static std::shared_ptr<Process<std::string>> ReadPipeContent(\n \t\tHANDLE process_handle, \n    bool keep_standard_output, \n    Type type = Type::NonBlocking, \n    std::string resourceType = \"\")",
      "language": "cplusplus"
    }
  ]
}
[/block]
  * **@IN HANDLE process_handle** Handle to the process.
  * **@IN  bool keep_standard_output**
  * **@IN Type type** If set to TRUE, the pipe content will also be pushed to
      the standard output (console). If set to FALSE, the pipe content will be completely
      captured.
* *NOTE* value passed directly to the guslib method
  The type of the process you want to start, defaults to NonBlocking
  * **@IN std::string resourceType**
 specifies the resource type you want to use. The application only takes this parameter in consideration if the type of the process is specified as *Blocking*.ResourceType defaults to empty string, this is not considered a process type by the application
[block:api-header]
{
  "type": "basic",
  "title": "Process Class"
}
[/block]
The Process class stores variables useful for the creation and management of processes. 
Its main function is to store the std::promise and std::function variables. 
* The std::promise represents the eventual value returned by the process 
*  std::function stores the method that will start the process.