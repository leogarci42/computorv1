#pragma once

#include <string>
#include <vector>

#include "./Token.hpp"

class Lexer {
	public:
		explicit Lexer(const std::string &input);
		std::vector<Token> tokenize();
	private:
		std::string m_input;
		size_t m_pos;

		void skipSpaces();
		Token readNumber();
};
