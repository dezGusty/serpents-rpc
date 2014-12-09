class Task{
  virtual void executeTask() = delete;
};

class NonBlockingTask : public Task{
  //non blocking method
};
class PriorityTask : public Task{
  //block all method
};
class BlockingTask :public Task{
  //blocking method
};