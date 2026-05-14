#pragma once

#include <string>

enum TokenType {
	TOK_NUMBER,
	TOK_PLUS,
	TOK_MINUS,
	TOK_STAR,
	TOK_CARET,
	TOK_EQUAL,
	TOK_VARIABLE,
	TOK_END
};

struct Token {
	TokenType type;
	std::string text;
	double number;
};

class token {
	protected:
		std::string all;
	public:
		std::string get_all() const {return (all);}
		void set_all(std::string tmp) {all = tmp;}
};
