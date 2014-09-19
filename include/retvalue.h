#ifndef RETVALUE_H
#define RETVALUE_H


#include <xmlrpc-c/base.hpp>
#include <xmlrpc++/XmlRpc.h>
#include <string>
/*
class RetValue{
public:
	enum type { Int, Float, Double, String, Bool };
private:

	type m_type;
	int m_int;
	double m_double;
	float m_float;
	std::string m_string;
	bool m_bool;
public:
	//does nothing
	RetValue(){}

	RetValue(int n){
		m_type = Int;
		m_int = n;
	}
	RetValue(double d){
		m_type = Double;
		m_double = d;
	}
	RetValue(std::string str){
		m_type = String;
		m_string = str;
	}
	RetValue(float f){
		m_type = Float;
		m_float = f;
	}
	RetValue(bool b){
		m_type = Bool;
		m_bool = b;
	}
	int getIntValue(){
		if (m_type == Int)
			return m_int;

	}
	double getDoubleValue(){
		if (m_type = Double){
			return m_double;
		}
	}
	float getFloatValue(){
		if (m_type == Float)
			return m_float;
	}
	std::string getStringValue(){
		if (m_type == String){
			return m_string;
		}
	}
	bool getBoolValue(){
		if (m_type == Bool){
			return m_bool;
		}
	}
	void setBoolValue(bool b){
		m_type = Bool;
		m_bool = b;
	}
	type getTYpe(){
		return m_type;
	}
	void setIntValue(int i){
		m_type = Int;
		m_int = i;
	}
	void setDoubleValue(double d){
		m_type = Double;
		m_double = d;
	}
	void setStringValue(std::string s){
		m_type = String;
		m_string = s;
	}
};
*/

class  RetValue{
public:
	virtual void setValue(int n) = 0;
	virtual void setValue(double n) = 0; 
	virtual void setValue(bool b) = 0; 
	virtual void setValue(std::string s) = 0; 

};


class XMLRPC_CRetValue: public RetValue{
public:
	void setValue(int n);
	void setValue(double n);
	void setValue(bool b);
	void setValue(std::string s);
	xmlrpc_c::value* getValue();
	XMLRPC_CRetValue();
	~XMLRPC_CRetValue();
private:
	class Impl;
	Impl* Impl_;
};
class XMLRPC_CRetValue::Impl{
	friend XMLRPC_CRetValue;
	xmlrpc_c::value* value;
};

class XMLRPC_CPPRetValue: public RetValue{
public:
	void setValue(int n);
	void setValue(double n);
	void setValue(bool b);
	void setValue(std::string s);
	XmlRpc::XmlRpcValue getValue();
	XMLRPC_CPPRetValue();
	~XMLRPC_CPPRetValue();
private:
	class Impl;
	Impl* Impl_;
	
};

class XMLRPC_CPPRetValue::Impl{
	friend XMLRPC_CPPRetValue;
	XmlRpc::XmlRpcValue value;
};

#endif