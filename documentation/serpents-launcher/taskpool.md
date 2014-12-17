##TaskPool
[TOC]
####TaskPool Class

~~~cpp
	class LAUNCHER_EXPORT_SYMBOL TaskPool{
  public:
    class Impl;
    Impl* Impl_;
    explicit TaskPool(int numWorkers = -1);
    ~TaskPool();
    void abort();
    void stop();  
    void waitForCompletion();
 
    template<typename RETVAL>
    std::future<RETVAL> addProcTask(std::shared_ptr<Process<RETVAL>> proc);
   
  private:
    void doWork();
    void joinAll();
    void operator=(const TaskPool&) = delete;
    TaskPool(const TaskPool&) = delete;
  };
~~~

#####TaskPool::Taskpool
_The constructor is used to specify the number of threads the applications will use. If no num. is specified the project defaults to the number of concurrent threads supported by the hardware implementation +1. Instantiates Impl._

**@IN: int numWorkers** number of threads the application will use
~~~cpp
explicit TaskPool(int numWorkers = -1);
~~~

#####TaskPool::~Taskpool
_Calls TaskPool::abort() to guarante all threads finish and no new threads are being added to the queue . Deletes Impl._
~~~cpp
~TaskPool();
~~~

#####TaskPool::stop
_Stops new threads from being added to the queue._
~~~cpp
void stop();  
~~~

#####TaskPool::abort
_Stops new threads from being added to the queue. Waits for current threads to complete. _
~~~cpp
void abort();
~~~

#####TaskPool::waitForCompletion
_Waits for the current threads to complete. Asserts that the thread queue is empty after this function completes. _
~~~cpp
void waitForCompletion();
~~~

#####TaskPool::addProcTask
_*NOTE:* the implementation for addProdTask is found in the  "addProdTask.inl" file_

_Takes as parameter a Process object, unpacks this object and creates a Task object, which it adds to the queue. Creates the link between the asyncronous std::future value and the return value of the lambda expression._

* **@IN std::shared_ptr<Process<RETVAL>> proc** process to be added to the queue. 
* **@OUT**: async value returned by the function. This completes when the user calls get() on the value

~~~cpp
template<typename RETVAL>
std::future<RETVAL> addProcTask(std::shared_ptr<Process<RETVAL>> proc);
~~~

#####TaskPool::doWork
_Member function used to initialize threads. The function pops the FIFO queue and calls the resulting Task exec() method._
~~~cpp
void doWork();
~~~
