##Serpents-rpc Example 
####Derive the serpents::Method base class
~~~cpp
class AddMethod : public  serpents::Method
{
  public:
  RPCMethod2()
  {
    //signature and help are used in the xmlrpc_c and xmlrpc++ plugins, can be ignored for serpents-ssl plugin
    setSignature(std::string("i:ii"));  
    setHelp(std::string("this method adds two ints together"));
	
	//sets the name of the method in the function repository. 
	//calls to the method will be made using this name
    setName("add");
  }
  //bloc of code that will execute when this method is called
  void execute(serpents::ParameterContainer* parameters, RetValue* rv)
  {
    int sum = 0;
    sum = parameters->getInt(0) + parameters->getInt(1);
    rv->setValue(sum);
  }
};
~~~


####Start the server 

~~~cpp
 serpents::Server server;
 serpents::FunctionRepository fr;
 
 //optional:: set log target
 server.addLogTarget("default", "D:\\program.log");
 AddMethod addmethod = new AddMethod(); 
 
 //add the method to the function repository
 fr.addMethod(addmethod);
  
 // set the server's function repository
 server.setRepository(fr);
 serpents::RPCSelector rpcselect;
 try
 {
 	//optional: set server characteristics
	server.getServerOptions()->portNumber(8080);
	server.getServerOptions()->uriPath("/RPC2");

	// pick server plugin
	rpcselect.selectRPCMethod(server, "serpents_ssl");

	//start the server  
	rpcselect.startServer();
	 
  }
  catch (const std::exception& e)
  {
    std::cout << e.what() << std::endl;
  }
 
  
 
~~~
