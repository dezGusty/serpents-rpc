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

`virtual int getTimeout()` 
	
  Returns the maximum time the process is allowed to live. 

[cleanUp][link1]
[link1]:#

`virtual void cleanUp()`

Starts the clean up for the process started by the current class. If the handle of the process is known the [closeProcessByHandle][l1]




*******

[l1]:processutil.md#test