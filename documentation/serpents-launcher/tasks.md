[block:api-header]
{
  "type": "basic",
  "title": "Task Base Class"
}
[/block]

[block:code]
{
  "codes": [
    {
      "code": "class Task {\n    public:\n     virtual int getTimeout() = 0;\n     virtual void cleanUp() =0;\n     virtual void exec()=0;\n     virtual ~Task() {};\n    };",
      "language": "cplusplus",
      "name": "Task Base Class"
    }
  ],
  "sidebar": true
}
[/block]
Adding types of tasks the application can execute is done through extending the Task base class.
[block:api-header]
{
  "type": "fn",
  "title": "int Task::getTimeout()"
}
[/block]
returns the time (in milliseconds) the process was set to timeout
[block:api-header]
{
  "type": "fn",
  "title": "void Task::exec()"
}
[/block]
Executes the lambda function passed to the task object. 
[block:api-header]
{
  "type": "fn",
  "title": "void Task::cleanUp()"
}
[/block]
Uses the methods found in processUtil.h to try and close the child process. If the Task object does not have access to the handle, it first tries to acquire that through the process name.
NOTE: killing a process through it's name kills all the processes with that name currently running on the system.
[block:api-header]
{
  "type": "basic",
  "title": "Task sub classes:"
}
[/block]
The behavior for each sub class is generally obtained through modifying the exec class with various mutexes or std::atomic<bool>s
[block:api-header]
{
  "type": "basic",
  "title": "NonBlockingTask"
}
[/block]
Multiple processes started by this class can run at the same time.
[block:api-header]
{
  "type": "basic",
  "title": "Blocking Task"
}
[/block]
Multiple processes started by this class can run at the same time unless they use the same resource type. (this is specified through the processFactory methods)
[block:api-header]
{
  "type": "basic",
  "title": "BlockingAllTask"
}
[/block]
When the exec method is called it forces all of the other threads to yeald.