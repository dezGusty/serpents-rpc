##Serpents ssl client
_Creates a ssl-rpc client for the serpents-rpc library_

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
