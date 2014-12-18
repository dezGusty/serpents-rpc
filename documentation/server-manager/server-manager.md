##Server Manager

_Namespace: serpents_
_Used to registed/unregister plugins for the serpents-rpc library_
~~~cpp
class SERVERMGR_EXPORT_SYMBOL ServerManagerUtil{
  private:
    class Impl;
    Impl* Impl_;
  public:
    ServerManagerUtil();
    ~ServerManagerUtil();
    void registerServer(const std::string name, ServerStartUp* server);
    void unregisterServer(const std::string name, ServerStartUp* server);
    static ServerStartUp* getServerPointer(const std::string& name);
  };
~~~
####ServerManagerUtil::registerServer
_Takes the name and the immplementation of the server and stores it into a std::map._
* **@IN: const std::string name** name of the server 
* **@IN: ServerStartUp* server** ptr to ServerStartUp implementation.

~~~cpp
void registerServer(const std::string name, ServerStartUp* server);
~~~

####ServerManagerUtil::unregisterServer
_If the name of the plugin is found it is erased from the container. Else, nothing happens._
* **@IN: const std::string name** name of the server 
* **@IN: ServerStartUp* server** ptr to ServerStartUp implementation.

~~~cpp 
void ServerManagerUtil::unregisterServer(const std::string name, ServerStartUp* server)
~~~

####ServerManagerUtil::getServerPointer
_If the name is found in the container a ptr to the server immplentation is returned, else returns nullptr._
* **@IN: const std::string name** name of the server 

~~~cpp
ServerStartUp* ServerManagerUtil::getServerPointer(const std::string& name)
~~~