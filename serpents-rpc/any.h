#ifndef ANY_H
#define ANY_H

#include <string>

struct any{
	enum type { Int, Float,Double, String, Bool};

	any(int   e) { INT = e; m_type = Int; }
	any(float e) { FLOAT = e; m_type = Float; }
	any(std::string e) { STRING = e; m_type = String; }
	any(double e) { DOUBLE = e; m_type = Double; }
	any(bool e) { BOOL = e; m_type = Bool; }
	type get_type() const { return m_type; }
	int get_int() const { return INT; }
	float get_float() const { return FLOAT; }
	std::string get_string() const { return STRING; }
private:
	type m_type;
	int   INT;
	float FLOAT;
	double DOUBLE;
	bool BOOL;
	std::string STRING;

};


#endif