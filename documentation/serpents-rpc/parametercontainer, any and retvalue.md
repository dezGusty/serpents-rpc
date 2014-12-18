##ParameterContainer
_namespace: serpents_


_Provides a simple way to store variables of different types inside a container. Mainly used as server methods parameters._

####Quick example

~~~cpp
// use the constructor or the add method to add values
ParameterContainer param(42,4.2,"hello",std::string("world"), true); 
  for each (std::string var in param.getAll())
  {
    std::cout << var << std::endl;
  }
~~~
####ParameterContainer::ParameterContainer
_Adds variables to vectors of their respective type._
**@IN: Args... args** variadic template, used to accept multiple parameters of different types.
~~~cpp
  template <class ...Args>
  ParameterContainer(Args... args);
~~~
####ParameterContainer::add
_Same as the constructor it adds variables to vectors of their respective type._
_NOTE: if variable type isn't supprted it throws an exception_
**@IN: Args... args** variadic template, used to accept multiple
~~~cpp
 void add(Args... args)
~~~

###ParameterContainer::ParameterContainer
_Copy constructor, copies the vectors found at ParameterContainer::Impl from one object to another_
~~~cpp
 ParameterContainer::ParameterContainer(const ParameterContainer& pc);
~~~

###ParameterContainer::getInts
_Returns a refferance to the vector holding the stored int values inside the container_
~~~cpp
std::vector<int>& ParameterContainer::getInts();
~~~

###ParameterContainer::getDoubles
_Returns a refferance to the vector holding the stored double values inside the container_

~~~cpp
std::vector<double>& ParameterContainer::getDouble();
~~~

###ParameterContainer::getStrings
_Returns a refferance to the vector holding the stored string values inside the container_
~~~cpp
std::vector<std::string>& ParameterContainer::getStrings();
~~~

###ParameterContainer::getBools
_Returns a refferance to the vector holding the stored bool values inside the container_
~~~~cpp
std::vector<bool>& ParameterContainer::getBools();
~~~

###ParameterContainer::getAll
_Returns a refference to a vector containing all the values added to the ParameterContainer converted to string values._
~~~cpp
std::vector<std::string>& ParameterContainer::getAll();
~~~

###ParameterContainer::geters
_Returns the value found at position n in the respective type vector. If no value is found throws ParamContainerException._
~~~cpp
bool ParameterContainer::getBool(unsigned int n);

int ParameterContainer::getInt(unsigned int n);

double ParameterContainer::getDouble(unsigned int n);

std::string ParameterContainer::getString(unsigned int n);

~~~

###ParameterContainer::size
_Returns the size of the vector containing all values stored as strings._
~~~cpp
unsigned int ParameterContainer::size()
~~~

###ParameterContainer::getType
_Returns the type of the variable found at position n._
~~~cpp
std::string ParameterContainer::getType(unsigned int n);
~~~

###ParameterContainer::parse
_Parses the variadic template._
_Creates a vector ```std::vector<any> vec = { args... };``` to figure out the type of the parameters. Depending on the type deduced by the [any][l1] class constructor it places the variable in the respective type vector. Also stores its type and the variable itself as a string in the 'All' vector._
~~~cpp
template <class ...Args>
void parse(const Args&... args)
~~~

###Any
_The any class is used to figure out the type of the variable passed to ParameterContainer::parse_
_NOTE: treats float as double for compatibility with the other xmlrpc libs used._
~~~cpp
class any
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
    explicit any(float e); 
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
~~~
##RetValue
_Abstract class that has to be derived by any plugins created for the serpents-rpc lib._
~~~cpp
class RetValue{
public:
  virtual void setValue(int n) = 0;
  virtual void setValue(double n) = 0;
  virtual void setValue(bool b) = 0;
  virtual void setValue(std::string s) = 0;
  virtual void setValue(float f) = 0;
};
~~~

[l1]:#Any