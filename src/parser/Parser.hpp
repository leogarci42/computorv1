#pragma once

#include <cstddef>
#include <vector>

#include "./Token.hpp"
#include "./Lexer.hpp"
#include "../model/Polynomial.hpp"

class parser : public token {
	public:
		void Parser();
	private:
		std::vector<Token> m_tokens;
		size_t m_pos;

		Polynomial parseEquation();
		void parseSide(int sideSign, Polynomial &poly);
		void parseTerm(int sideSign, Polynomial &poly);
		const Token &peek() const;
		const Token &advance();
		bool match(TokenType type);
};
