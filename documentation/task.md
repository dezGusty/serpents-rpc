## Task Base Class 


********
~~~cpp 
class LAUNCHER_EXPORT_SYMBOL Task {
    public:
     virtual int getTimeout() = 0;
     virtual void cleanUp() =0;
     virtual void exec()=0;
     virtual ~Task() {};
    };	
 }
~~~
#####Task::getTimeout
~~~cpp
virtual int getTimeout()
~~~
  Returns the maximum time the process is allowed to live. 

#####Task::cleanUp
~~~cpp
virtual void cleanUp()
~~~

Starts the clean up for the process started by the current class. If the handle of the process is known the [closeProcessByHandle][l1] method is used. If not, the application uses [closeProcessByName][l2].
_Note:_ [closeProcessByName][l2] kills all processes with the same name curently running on the system. 

#####Task::exec

~~~~cpp
virtual void exec();
~~~

Calls the std::function stored in the Task subclass. 

## Task Sub Classes

_The behavior for each sub class is generally obtained through modifying the exec class with various mutexes or std::atomic<bool>s_

####NonBlockingTask

Multiple processes started by this class can run at the same time.

####BlockingTask
Multiple processes started by this class can run at the same time unless they use the same resource type. this is specified through the [processFactory][l3] methods.

####BlockingAllTask
When the exec method is called it forces all of the other threads to yeald.
_Note:_ this behavior causes a race between the threads that were forced to yeald. Can not guarantee which thread executes firts. 

*******


[l1]:processutil.md#closeProcessByHandle
[l2]:processutil.md#closeProcessByName
[l3]:processfactory.md#processFactory