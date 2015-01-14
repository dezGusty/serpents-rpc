_namespace: serpents_

###Method
_Abstract class that needs to be derived by any class that will be added to the server's [FunctionRepository][l1]. Sub classes need to override the execute method._
~~~cpp
class SERPENTSDLL Method{
  protected:
    class Impl;
    Impl* Impl_;
  public:
    Method();
    ~Method();
    virtual std::string getSignature();
    virtual std::string getHelp();
    virtual void setSignature(std::string sig);
    virtual void setHelp(std::string help);
    virtual void setName(std::string name);
    virtual std::string Method::getName();
    virtual void execute(ParameterContainer* parameters, RetValue* rv) = 0;
    Method& operator=(Method& m);
    Method(const Method& m);
  };
~~~

###ServerStartUp
_Abstract class that needs to be derived by any plugin written for the serpents-rpc library._

_```std::thread& execute(Server* server)``` creates two threads,  one 'execution' thread and one 'controll' thread initialized with the ```run(Server* server)``` and ```controll``` methods._

```ServerOptions* getImplServerOptions()``` returns an implementation of the [ServerOptions][l2] abstract class.
~~~cpp
class ServerStartUp{
  public:
  virtual std::thread& execute(Server* server) = 0;
  virtual void run(Server* server) = 0;
  virtual void controll() = 0;
  virtual void start() = 0;
  virtual void stop() = 0;
  virtual ServerOptions* getImplServerOptions() = 0;
  };
~~~

###FunctionRepository
_Stores classes that derive the [Method][l3] base class. _
~~~cpp
class FunctionRepository{
  private:
    class  Impl;
    Impl* Impl_;
  public:
    FunctionRepository();
    typedef std::map<std::string, Method *> methodMap;
    void addMethod(Method* method);
    FunctionRepository& operator=(FunctionRepository& fr);
    FunctionRepository(FunctionRepository& fr);
    Impl* getImpl();
  };
~~~

###RPCSelector
_Selects the plugin that will be used as a server in the serpents-rpc library. Contains the logic to dynamically load and unload plugins._

_Contains a pointer to the startup implementation of the plugin and the [server][l4]_

	void RPCSelector::selectRPCMethod(Server& server, std::string plugInName)
choose the plugin you want to start.
The methods tries to load the plugin using ```guslib::DynamicLibManager::getPtr()->load(pluginName)```. If the plugin isn't found throws an exception.
	
	startServer()
Creates the execution and and controll threads. Then calls the start() method of the [ServerStartUp][l5] immplementation.
	
	stopServer()
Does not actually do anything.
~~~cpp
class RPCSelector
  {
  private:
    ServerStartUp* ServerStartUpImpl_;
    Server* server_;
  public:
    void startServer();
    void selectRPCMethod(Server& server, std::string method);
    void stopServer();
    RPCSelector();
    ~RPCSelector();
    RPCSelector(const  RPCSelector&) = delete;
  };
~~~
[l1]:#FunctionRepository
[l2]:#ServerOptions
[l3]:#Method
[l4]:#Server
[l5]:#ServerStartUp