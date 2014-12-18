
##Serpents ssl client
_Creates a ssl-rpc client for the serpents-rpc library_

####Example usage
~~~cpp
int main(){
	std::string host("localhost");  // host
	std::string port("8080");  // port

	boost::asio::io_service io_service;
	boost::asio::ip::tcp::resolver resolver(io_service);
	boost::asio::ip::tcp::resolver::query query(host, port);
	boost::asio::ip::tcp::resolver::iterator iterator = resolver.resolve(query);
	//ssl context 
	boost::asio::ssl::context ctx(boost::asio::ssl::context::sslv23); // the server/client accepts sslv23 or higher to begin the secure connection
    ctx.load_verify_file("ca.pem"); // CA certificate file

	client c(io_service,ctx,iterator);

	//method parameters
	serpents::ParameterContainer request;
	serpents::ParameterContainer reply;
	request.add(2,3)

	//send the request to the rpc server
	c.send("add", request, reply);
	
	//get the result
	std::cout<<reply.getInt(0)<<std::endl;
	return 0;
} // main
~~~
####client::client

_The Constructor binds [verify_certificate][l1] and [handle_connect][l2] to the ssl socket as asynchronous methods.
It sets the socket's verify mode to boost::asio::ssl::verify_peer (hardcoded)._
[[Boost ssl doc]](http://www.boost.org/doc/libs/1_56_0/doc/html/boost_asio/overview/ssl.html)

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

###client::send

Sends a https post to the host and port specified with the parameters specified in 'serpents::ParameterContainer* request'and attempts to call the speciffied server method. If the call succedes the result is stored inside 'serpents::ParameterContainer* reply'.
*NOTE: starts boost::io_service.* 
* **@IN: const std::string& methodName ** The xml-rpc server method called
* **@IN: serpents::ParameterContainer\* request** holds request parameters
* **@IN: serpents::ParameterContainer\* reply** holds reply parameters
~~~cpp
void send(const std::string& methodName, serpents::ParameterContainer* request, serpents::ParameterContainer* reply)
~~~

####client::verify_certificate
* **@IN: bool preverified**,
* **@IN: boost::asio::ssl::verify_context& ctx**
 arguments used for the set_verify_callback. The callback is called once for each certificate in the chain starting from the root certificate. 
 
~~~cpp
bool verify_certificate(bool preverified,
      boost::asio::ssl::verify_context& ctx)
~~~

####client::handle_connect
_Asynchronously calls [handle_handshake][l3]._
**@IN: const boost::system::error_code& error**  Shows if any error occoured in the previous asynch method. 
~~~cpp
 void handle_connect(const boost::system::error_code& error)
~~~
####client::handle_handshake
_Asynchronously calls [handle_write][l4]. Begins building the https post request. _
**@IN: const boost::system::error_code& error**  Shows if any error occoured in the previous asynch method. 
~~~cpp
 void handle_handshake(const boost::system::error_code& error)
~~~

####client::handle_write
_Asynchronously calls [handle_read][l5]. Writes message to server._
* **@IN: const boost::system::error_code& error**  Shows if any error occoured in the previous asynch method. 
* **@IN: size_t bytes_transferred** bytes transferred in the previous method
~~~cpp
void handle_write(const boost::system::error_code& error, 
                  size_t bytes_transferred)
~~~

####client::handle_read
_Reads from the client. Decodes the xml rpc file and stores the variables inside a ParameterContainer._
* **@IN: const boost::system::error_code& error**  Shows if any error occoured in the previous asynch method.
* **@IN: size_t bytes_transferred** bytes transferred in the previous method. Used to determine how many bytes the client should read, now the client reads until the string "</ messageResponse>" is found. 
~~~cpp
void handle_read(const boost::system::error_code& error,
                 size_t bytes_transferred)
~~~
[l1]:#client::verify_certificate
[l2]:#client::handle_connect
[l3]:#client::handle_handshake
[l4]:#client::handle_write
[l5]:#client::handle_read
