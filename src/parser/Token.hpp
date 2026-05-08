#pragma once

#include <iostream>
#include <string>

typedef enum e_token {
	ADD,
	SUB,
	MULT,
	DIV,
	EXP,
	NUM,
	CONST
} t_token;

class token {
	protected:
		t_token *type;
		std::string *val;
		std::string all;
	public:
		std::string *get_val() const {return (val);}
		std::string get_all() const {return (all);}
		t_token *get_token() const {return (type);}
		void set_val(std::string tmp, int i) {val[i] = tmp;}
		void set_all(std::string tmp) {all = tmp;}
		void set_token(t_token tmp, int i) {type[i] = tmp;}
};
