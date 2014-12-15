
  template<typename RETVAL>
  std::future<RETVAL> TaskPool::addProcTask(std::shared_ptr<Process<RETVAL>> proc){
    std::future<RETVAL> future = proc->data_->first.get_future();
    std::shared_ptr<Task*> task;
    switch (proc->type_){
    case Type::Blocking: 
      {
        task = std::make_shared<Task*>(new BlockingTask(
           proc->process_to_execute_,
          proc->maximum_timeout_in_millis_,
          proc->Handle_,
          [proc](){
          try{
            proc->data_->first.set_value(proc->data_->second());
          }
          catch (...){
            proc->data_->first.set_exception(std::current_exception());
          }
          }));
      } break;
     case Type::NonBlocking:
      {
        task = std::make_shared<Task*>(new NonBlockingTask(
           proc->process_to_execute_,
          proc->maximum_timeout_in_millis_,
          proc->Handle_,
          [proc](){
          try{
            proc->data_->first.set_value(proc->data_->second());
          }
          catch (...){
            proc->data_->first.set_exception(std::current_exception());
          }
          }));
      } break;
    }

    Impl_->taskQue_.emplace_back(task);

    return std::move(future);
  }
  
  template<>
  std::future<void> TaskPool::addProcTask(std::shared_ptr<Process<void>> proc){
    std::future<void> future = proc->data_->first.get_future();
    std::shared_ptr<Task*> task;
    switch (proc->type_){
    case Type::Blocking: 
    {
    task = std::make_shared<Task*>(new BlockingTask(
           proc->process_to_execute_,
          proc->maximum_timeout_in_millis_,
          proc->Handle_,
          [proc](){
          try{
            proc->data_->first.set_value();
            proc->data_->second();
          }
          catch (...){
            proc->data_->first.set_exception(std::current_exception());
          }
          }));
    } break;
      case Type::NonBlocking:
        {
          task= std::make_shared<Task*>(new NonBlockingTask(
            proc->process_to_execute_,
            proc->maximum_timeout_in_millis_,
            proc->Handle_,
            [proc](){
            try{
              proc->data_->first.set_value();
              proc->data_->second();
            }
            catch (...){
              proc->data_->first.set_exception(std::current_exception());
            }
          }));
        }
        break; 
      default: break;
    }
    
    Impl_->taskQue_.emplace_back(task);
   
    return std::move(future);
  }
