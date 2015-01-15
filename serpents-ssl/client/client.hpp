#ifndef SSL_CLIENT_HPP_
#define SSL_CLIENT_HPP_

//   This file is part of the serpents-rpc library, licensed under the terms of the MIT License.
//
//   The MIT License
//   Copyright (C) 2010-2014  The serpents-rpc team (See AUTHORS file)
//
//   Permission is hereby granted, free of charge, to any person obtaining a copy
//   of this software and associated documentation files (the "Software"), to deal
//   in the Software without restriction, including without limitation the rights
//   to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//   copies of the Software, and to permit persons to whom the Software is
//   furnished to do so, subject to the following conditions:
//
//   The above copyright notice and this permission notice shall be included in
//   all copies or substantial portions of the Software.
//
//   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//   OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
//   THE SOFTWARE.


//  project libs
#include "serpents-rpc\serpents\rpc\parameters\parametercontainer.hpp"
#include "serpents-ssl\util\xmlutil.hpp"

//  boost libs
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>

//  c++ system libs
#include <string>



// #define PUGIXML_HEADER_ONLY
enum 
{ 
  max_length =2024 
};

class client
{
  public:
  client(boost::asio::io_service& io_service,
      boost::asio::ssl::context& context,
      boost::asio::ip::tcp::resolver::iterator endpoint_iterator)
    : io_service_(io_service),
      socket_(io_service_, context)
  {
  XMLParser_ = new serpents::util::xml::PugiXML;
    socket_.set_verify_mode(boost::asio::ssl::verify_peer);
    socket_.set_verify_callback(
        boost::bind(&client::verify_certificate, this, _1, _2));

    boost::asio::async_connect(socket_.lowest_layer(), endpoint_iterator,
        boost::bind(&client::handle_connect, this,
          boost::asio::placeholders::error));
  }

  bool verify_certificate(bool preverified,
      boost::asio::ssl::verify_context& ctx)
  {
    // The verify callback can be used to check whether the certificate that is
    // being presented is valid for the peer. For example, RFC 2818 describes
    // the steps involved in doing this for HTTPS. Consult the OpenSSL
    // documentation for more details. Note that the callback is called once
    // for each certificate in the certificate chain, starting from the root
    // certificate authority.

    // In this example we will simply print the certificate's subject name.
    char subject_name[256];
    X509* cert = X509_STORE_CTX_get_current_cert(ctx.native_handle());
    X509_NAME_oneline(X509_get_subject_name(cert), subject_name, 256);
  

    return preverified;
  }
  void handle_connect(const boost::system::error_code& error)
  {
    if (!error)
    {
      socket_.async_handshake(boost::asio::ssl::stream_base::client,
        boost::bind(&client::handle_handshake, this,
        boost::asio::placeholders::error));
    }
    else
    {
      std::cout << "Connect failed: " << error.message() << "\n";
    }
  }

  void handle_handshake(const boost::system::error_code& error)
  {
    if (!error)
    {
      std::stringstream buff = buildPostRequest();
      strcpy_s(request_, buff.str().c_str());
      size_t request_length = strlen(request_);

      boost::asio::async_write(socket_,
        boost::asio::buffer(request_, request_length),
        boost::bind(&client::handle_write, this,
        boost::asio::placeholders::error,
        boost::asio::placeholders::bytes_transferred));
    }
    else
    {
      std::cout << "Handshake failed: " << error.message() << "\n";
    }
  }

  void handle_write(const boost::system::error_code& error, size_t bytes_transferred)
  {
    if (!error)
    {
      //  Normal method didn't work. For some reason it didn't recieve all of the message. 
      //  The received message should always end in </methodResponse> if the client implements
      //  the xmlrpc protocol.
      //  BUT, if the client ommits that, it causes the server to read continously. 
      boost::asio::async_read_until(socket_,
        reply_,
        "</methodResponse>",
        boost::bind(&client::handle_read, this,
        boost::asio::placeholders::error,
        boost::asio::placeholders::bytes_transferred));
    }
    else
    {
      std::cout << "Write failed: " << error.message() << "\n";
    }
  }

  void handle_read(const boost::system::error_code& error, size_t bytes_transferred)
  {
    std::ostringstream ss;
    ss << &reply_;
    std::string s = ss.str();
    XMLParser_->getResponseParameters(s, *replyParam_);
  }
  void send(const std::string& methodName, serpents::ParameterContainer* request, serpents::ParameterContainer* reply)
  {
    requestParam_ = request;
    replyParam_ = reply;
    methodName_ = methodName;
    io_service_.run();
  }

  std::stringstream buildPostRequest()
  {
    std::string result = XMLParser_->generateXMLDoc(methodName_, requestParam_, result);
    std::stringstream buff;
    buff << "POST /RPC2 HTTP/1.1\r\n";
    buff << "Host: localhost:8080\r\n";
    buff << "Content-Length: " << result.length()<< "\r\n\r\n";
    buff << result;
    return buff;
  }
  private:
  serpents::ParameterContainer* requestParam_;
  serpents::ParameterContainer* replyParam_;
  std::string methodName_;
  serpents::util::xml::IXMLClass* XMLParser_;
  boost::asio::io_service& io_service_;
  boost::asio::ssl::stream<boost::asio::ip::tcp::socket> socket_;
  char request_[max_length];
  boost::asio::streambuf reply_;
  boost::array<char, max_length> buffer_;
};

#endif  // SSL_CLIENT_HPP_
