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

//  gtest libs
#include "gtest\gtest.h"

//  c++ system libs
#include <cstdlib>
#include <cmath>
#include <string>

// xmlrpc_c libs
#include <xmlrpc-c/girerr.hpp>
#include <xmlrpc-c/base.hpp>
#include <xmlrpc-c/client_simple.hpp>
using std::string;

TEST(fileLookUp, fileExists)
{
  xmlrpc_c::clientSimple myClient;
  xmlrpc_c::value result2;
  myClient.call("http://localhost:8080/RPC2", "fileLookUp", "s", &result2, "D:\\test.txt");
  bool response = xmlrpc_c::value_boolean(result2);
  EXPECT_EQ(true, response);
}

TEST(fileLookUp, fileDoesNotExists)
{
  xmlrpc_c::clientSimple myClient;
  xmlrpc_c::value result2;
  myClient.call("http://localhost:8080/RPC2", "fileLookUp", "s", &result2, "D:\\test2.txt");
  bool response = xmlrpc_c::value_boolean(result2);
  EXPECT_EQ(false, response);
}


TEST(sleep, returns)
{
  xmlrpc_c::clientSimple myClient;
  xmlrpc_c::value result2;
  myClient.call("http://localhost:8080/RPC2", "sleep", "i", &result2, 5);
  bool response = xmlrpc_c::value_boolean(result2);
  EXPECT_EQ(true, response);
}
TEST(getMean, positive)
{
  xmlrpc_c::clientSimple myClient;
  xmlrpc_c::paramList getMeanParms;
  xmlrpc_c::value result;
  getMeanParms.add(xmlrpc_c::value_int(2));
  getMeanParms.add(xmlrpc_c::value_double(0.5));
  getMeanParms.add(xmlrpc_c::value_int(2));
  getMeanParms.add(xmlrpc_c::value_double(0.5));
  myClient.call("http://localhost:8080/RPC2", "getMean", getMeanParms, &result);
  float response = xmlrpc_c::value_double(result);
  float res = 2.0f;
  EXPECT_EQ(res, response);
}

TEST(getMean, negative)
{
  xmlrpc_c::clientSimple myClient;
  xmlrpc_c::paramList getMeanParms;
  xmlrpc_c::value result;
  getMeanParms.add(xmlrpc_c::value_int(-2));
  getMeanParms.add(xmlrpc_c::value_double(-0.5));
  getMeanParms.add(xmlrpc_c::value_int(-2));
  getMeanParms.add(xmlrpc_c::value_double(-0.5));
  myClient.call("http://localhost:8080/RPC2", "getMean", getMeanParms, &result);
  float response = xmlrpc_c::value_double(result);
  float res = -2.0f;
  EXPECT_EQ(res, response);
}
TEST(getMean, other)
{
  xmlrpc_c::clientSimple myClient;
  xmlrpc_c::paramList getMeanParms;
  xmlrpc_c::value result;
  getMeanParms.add(xmlrpc_c::value_int(4));
  getMeanParms.add(xmlrpc_c::value_double(0.5));
  getMeanParms.add(xmlrpc_c::value_int(4));
  getMeanParms.add(xmlrpc_c::value_double(0.5));
  myClient.call("http://localhost:8080/RPC2", "getMean", getMeanParms, &result);
  float response = xmlrpc_c::value_double(result);
  float res = 4.0f;
  EXPECT_EQ(res, response);
}
TEST(push)
{
  xmlrpc_c::clientSimple myClient;
  xmlrpc_c::value result;
  myClient.call("http://localhost:8080/RPC2", "push", "s", &result, "test");
  bool pushResponse = xmlrpc_c::value_boolean(result);
  EXPECT_EQ(true, pushResponse);
}
TEST(pop)
{
  xmlrpc_c::clientSimple myClient;
  xmlrpc_c::value result;
  myClient.call("http://localhost:8080/RPC2", "pop", "s", &result, "");

  std::string sr = xmlrpc_c::value_string(result);

  EXPECT_EQ("test", sr);
}
TEST(generateUUID)
{
  xmlrpc_c::clientSimple myClient;
  xmlrpc_c::value randomString;
  myClient.call("http://localhost:8080/RPC2", "generateUUID", "s", &randomString, "");
  std::string uuidResponse = xmlrpc_c::value_string(randomString);
  std::cout << uuidResponse << std::endl;
}
int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
