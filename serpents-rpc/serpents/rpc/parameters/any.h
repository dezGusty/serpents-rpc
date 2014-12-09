#ifndef ANY_H_
#define ANY_H_
// system libs 
#include <string>

// project libs
#include "serpents\rpc\base.h"
namespace serpents
{
  class SERPENTSDLL any
  {
  public:
    enum type 
    { 
      Int, Float, Double, String, Bool
    };
    explicit any(int   e);
    explicit any(std::string e);
    explicit any(const char* e);
    explicit any(double e);
    explicit any(float e); // treat float as double for compatibility with other xmlrpc libs
    explicit any(bool e);
    any(const any& a);
    ~any();
    type get_type() const;
    double get_double() const;
    int get_int() const;
    std::string get_string() const;
    bool get_bool() const;
  private:
    class Impl;
    Impl* Impl_;
  };
}
#endif  //  ANY_H_
