#include "serpents\rpc\parameters\any.h"

namespace serpents
{
  // any
  class any::Impl
  {
    friend any;
    any::type m_type;
    int   INT = 0;
    double DOUBLE = 0;
    bool BOOL = 0;
    std::string STRING = "";
  };
  any::any(int   e)
  {
    Impl_ = new Impl;
    Impl_->INT = e;
    Impl_->m_type = type::Int;
  }
  any::any(std::string e)
  {
    Impl_ = new Impl;
    Impl_->STRING = e;
    Impl_->m_type = type::String;
  }
  any::any(const char* e)
  {
    Impl_ = new Impl;
    Impl_->STRING = e;
    Impl_->m_type = type::String;
  }
  any::any(double e)
  {
    Impl_ = new Impl;
    Impl_->DOUBLE = e;
    Impl_->m_type = type::Double;
  }
  any::any(float e) // treat float as double for compatibility with other xmlrpc libs
  {
    Impl_ = new Impl;
    Impl_->DOUBLE = e;
    Impl_->m_type = type::Double;
  }
  any::any(bool e)
  {
    Impl_ = new Impl;
    Impl_->BOOL = e;
    Impl_->m_type = type::Bool;
  }
  any::type any::get_type() const
  {
    return Impl_->m_type;
  }
  double  any::get_double() const
  {
    return Impl_->DOUBLE;
  }
  int  any::get_int() const
  {
    return Impl_->INT;
  }
  std::string any::get_string() const
  {
    return Impl_->STRING;
  }
  bool  any::get_bool() const
  {
    return Impl_->BOOL;
  }  // end any

  any::~any()
  {
    delete Impl_;
  }
  any::any(const any& a)
  {
    this->Impl_ = new Impl;
    this->Impl_->m_type = a.Impl_->m_type;
    this->Impl_->INT = a.Impl_->INT;
    this->Impl_->DOUBLE = a.Impl_->DOUBLE;
    this->Impl_->BOOL = a.Impl_->BOOL;
    this->Impl_->STRING = a.Impl_->STRING;
  }
}