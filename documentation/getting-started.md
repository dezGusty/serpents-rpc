[block:api-header]
{
  "type": "basic",
  "title": "Method class"
}
[/block]
The basic method class used by serpents-rpc function repository. A class needs to extends this in order to be used. 
[block:code]
{
  "codes": [
    {
      "code": "class SERPENTSDLL Method{\n  protected:\n    class Impl;\n    Impl* Impl_;\n  public:\n    Method();\n    ~Method();\n    virtual std::string getSignature();\n    virtual std::string getHelp();\n    virtual void setSignature(std::string sig);\n    virtual void setHelp(std::string help);\n    virtual void setName(std::string name);\n    virtual std::string Method::getName();\n    virtual void execute(ParameterContainer* parameters, RetValue* rv) = 0;\n    Method& operator=(Method& m);\n    Method(const Method& m);\n  };",
      "language": "cplusplus",
      "name": "Base Class"
    },
    {
      "code": "class RPCMethod2 :public  serpents::Method{\npublic:\n  RPCMethod2(){\n  \n    setSignature(std::string(\"i:ii\"));\n    setHelp(std::string(\"this method adds two ints together\"));\n    setName(\"add\");\n  }\n  void execute(serpents::ParameterContainer* parameters, RetValue* rv){\n    int sum= 0;\n    sum = parameters->getInt(0) + parameters->getInt(1);\n    rv->setValue(sum);\n  }\n  \n};\n",
      "language": "c",
      "name": "Example usage"
    }
  ],
  "sidebar": true
}
[/block]
Name needs to be set in order for serpents-rpc to run. Help and signature should be set in order to avoid problems with the xmlrpc libraries used. 
[block:api-header]
{
  "type": "fn",
  "title": "addMethod"
}
[/block]
Function takes a pointer to a class that derives the base class Method.
[block:api-header]
{
  "type": "fn",
  "title": "setRepository"
}
[/block]
Used to give the server the functions it will execute. Since the name of the methods needs to be set when defining the class, this method automatically sets the name as the url path that the function will be accessed.
[block:code]
{
  "codes": [
    {
      "code": "void setRepository(FunctionRepository& fr){",
      "language": "text"
    }
  ]
}
[/block]

[block:api-header]
{
  "type": "fn",
  "title": "selectRPCMethod"
}
[/block]

[block:code]
{
  "codes": [
    {
      "code": "void selectRPCMethod(Server& server, std::string method)",
      "language": "text"
    }
  ]
}
[/block]

[block:api-header]
{
  "type": "basic",
  "title": "RPCSelector"
}
[/block]
Class used to set the function repository for the server. It contains the logic to start and stop the server
[block:api-header]
{
  "type": "basic",
  "title": "void startServer()"
}
[/block]
Starts the server. Since that after starting the server the underlying server implementation takes away control, the only way to close the server is through an outside interruption. At this time the only implemented method is to type "exit" in the console.  
[block:api-header]
{
  "type": "basic",
  "title": "Quick Example"
}
[/block]
Start by extending the base class "Method". A quick example:
[block:code]
{
  "codes": [
    {
      "code": "class RPCMethod2 :public  serpents::Method{\npublic:\n  RPCMethod2(){\n  \n    setSignature(std::string(\"i:ii\"));\n    setHelp(std::string(\"this method adds two ints together\"));\n    setName(\"add\");\n  }\n  void execute(serpents::ParameterContainer* parameters, RetValue* rv){\n    int sum= 0;\n    sum = parameters->getInt(0) + parameters->getInt(1);\n    rv->setValue(sum);\n  }\n  \n};",
      "language": "c"
    }
  ]
}
[/block]
Initialize your class and the function repo, use the addMethod function to add the newly instantiated class. 
[block:code]
{
  "codes": [
    {
      "code": "RPCMethod* rpc = new RPCMethod();\nserpents::FunctionRepository fr;\nfr.addMethod(rpc);",
      "language": "c"
    }
  ]
}
[/block]

[block:code]
{
  "codes": [
    {
      "code": "serpents::Server server;\nserver.setRepository(fr);\nserpents::RPCSelector rpcselect;\nrpcselect.selectRPCMethod(server, \"xmlrpc_c\");\nrpcselect.startServer();",
      "language": "c"
    }
  ]
}
[/block]
Instantiate the server, set the repository with the function you want to be able to call. Selecting the server means (at this point) passing a string with the name of the xmlrpc libreary you want to use. Then just start the server.