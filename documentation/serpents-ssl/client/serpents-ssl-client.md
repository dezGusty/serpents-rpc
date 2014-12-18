
##Serpents ssl client
_Creates a ssl-rpc client for the serpents-rpc library_

####Example usage
~~~cpp
int main(){
	std::string host("localhost");
	std::string port("8080");

	boost::asio::io_service io_service;
	boost::asio::ip::tcp::resolver resolver(io_service);
	boost::asio::ip::tcp::resolver::query query(host, port);
	boost::asio::ip::tcp::resolver::iterator iterator = resolver.resolve(query);
	//ssl context 
	boost::asio::ssl::context ctx(boost::asio::ssl::context::sslv23); // the server/client accepts sslv23 or higher
	                                                                  //to begin the secure connection
    ctx.load_verify_file("ca.pem"); // CA certificate file

	client c(io_service,ctx,iterator);

	//method parameters
	serpents::ParameterContainer request;
	serpents::ParameterContainer reply;
	request.add(2,3)

	//send the request to the rpc server 
	c.send("add", &request, &reply);
	
	//get the result
	std::cout<<reply.getInt(0)<<std::endl;
	return 0;
} // main
~~~
####client::client

_The Constructor verifies the CA cerificate through the [verify_certificate][l1] method and, if the certificate is valid, it tries to connect to the server through [handle_connect][l2].
It sets the socket's verify mode to boost::asio::ssl::verify_peer (hardcoded)._

* **@IN: [boost::asio::io_service& io_service](http://www.boost.org/doc/libs/1_56_0/doc/html/boost_asio/reference/io_service.html)** 
provides the core I/O functionality for users of the asynchronous I/O objects
* **@IN:[boost::asio::ssl::context& context](http://www.boost.org/doc/libs/1_56_0/doc/html/boost_asio/reference/ssl__context.html)** 
contains the CA certificate. 
* **@IN:[boost::asio::ip::tcp::resolver::iterator endpoint_iterator](http://www.boost.org/doc/libs/1_56_0/doc/html/boost_asio/reference/ip__basic_resolver/iterator.html)** query resolver 


~~~cpp
client(boost::asio::io_service& io_service,
      boost::asio::ssl::context& context,
      boost::asio::ip::tcp::resolver::iterator endpoint_iterator)
~~~

####client::verify_certificate
* **@IN: bool preverified**,
* **@IN: boost::asio::ssl::verify_context& ctx**
 arguments used for the set_verify_callback. The callback is called once for each certificate in the chain starting from the root certificate. 
~~~cpp
bool verify_certificate(bool preverified,
      boost::asio::ssl::verify_context& ctx)
~~~
[l1]:#client::verify_certificate
[l2]:#client::handle_connect
