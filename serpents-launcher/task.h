class Task{
public:
  virtual void executeTask() = 0;
};

class NonBlockingTask : public Task{
  void executeTask(){
    
  }
};
class PriorityTask : public Task{
  //block all method
};
class BlockingTask :public Task{
  //blocking method
};