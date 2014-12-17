*NOTE:* the implementation for addProdTask is found in the  "addProdTask.inl" file
[block:api-header]
{
  "type": "basic",
  "title": "TaskPool Class"
}
[/block]

[block:code]
{
  "codes": [
    {
      "code": " class LAUNCHER_EXPORT_SYMBOL TaskPool{\n  public:\n    class Impl;\n    Impl* Impl_;\n    explicit TaskPool(int numWorkers = -1);\n    ~TaskPool();\n    void abort();\n    void stop();  \n    void waitForCompletion();\n \n    template<typename RETVAL>\n    std::future<RETVAL> addProcTask(std::shared_ptr<Process<RETVAL>> proc);\n   \n  private:\n    void doWork();\n    void joinAll();\n    void operator=(const TaskPool&) = delete;\n    TaskPool(const TaskPool&) = delete;\n  };",
      "language": "cplusplus",
      "name": "TaskPool"
    }
  ]
}
[/block]

[block:api-header]
{
  "type": "basic",
  "title": "TaskPool::Taskpool(int numWorkers = -1)"
}
[/block]
The constructor is used to specify the number of threads the applications willuse. If no num. is specified the project defaults to the number of concurrent threads supported by the hardware implementation +1.
[block:code]
{
  "codes": [
    {
      "code": "explicit TaskPool(int numWorkers = -1);",
      "language": "cplusplus",
      "name": "TaskPool"
    }
  ]
}
[/block]
**@IN int numWorkers** number of threads the application will use