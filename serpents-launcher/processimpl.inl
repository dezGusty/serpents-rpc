class Process::Impl{
  friend Process;
  std::string process_to_execute_;
  int maximum_timeout_in_millis_;
  HANDLE Handle_;
  std::shared_ptr<pair_t> data_;
};

Process(const std::string& process_to_execute, int maximum_timeout_in_millis, std::function<RETVAL()>&& function)
:process_to_execute_(process_to_execute),
maximum_timeout_in_millis_(maximum_timeout_in_millis),
Handle_(nullptr)
{
  data_ = std::make_shared<pair_t>(std::promise<RETVAL>(), std::move(function));
}
Process(HANDLE Handle, int maximum_timeout_in_millis, std::function<RETVAL()>&& function)
:process_to_execute_(""),
maximum_timeout_in_millis_(maximum_timeout_in_millis),
Handle_(Handle)
{
  data_ = std::make_shared<pair_t>(std::promise<RETVAL>(), std::move(function));
}
Process(HANDLE Handle, std::function<RETVAL()>&& function)
:process_to_execute_(""),
maximum_timeout_in_millis_(-1),
Handle_(Handle)
{
  data_ = std::make_shared<pair_t>(std::promise<RETVAL>(), std::move(function));
}
Process(std::function<RETVAL()>&& function)
:process_to_execute_(""),
maximum_timeout_in_millis_(-1),
Handle_(nullptr)
{
  data_ = std::make_shared<pair_t>(std::promise<RETVAL>(), std::move(function));
}

