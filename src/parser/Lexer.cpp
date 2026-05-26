#include "Lexer.hpp"

#include <cctype>

#include "../utils/Exceptions.hpp"

Lexer::Lexer(const std::string &input) : m_input(input), m_pos(0) {}

void Lexer::skipSpaces()
{
	while (m_pos < m_input.size() && std::isspace(static_cast<unsigned char>(m_input[m_pos])))
		++m_pos;
}

Token Lexer::readNumber()
{
	size_t start = m_pos;
	bool seenDot = false;
	bool seenDigit = false;
	double value = 0.0;

    while (m_pos < m_input.size())
    {
		char c = m_input[m_pos];
		if (std::isdigit(static_cast<unsigned char>(c)))
        {
			seenDigit = true;
			int digit = c - '0';
			value = value * 10.0 + digit;
			++m_pos;
			continue;
		}
		if (c == '.' && !seenDot)
        {
			seenDot = true;
			++m_pos;
			break;
		}
		break;
	}

	if (seenDot)
    {
		double factor = 0.1;
		while (m_pos < m_input.size())
        {
			char c = m_input[m_pos];
			if (!std::isdigit(static_cast<unsigned char>(c)))
				break;
			seenDigit = true;
			int digit = c - '0';
			value += digit * factor;
			factor *= 0.1;
			++m_pos;
		}
	}

	if (!seenDigit)
		throw ParseError("Invalid number literal.");
	Token token;
	token.type = TOK_NUMBER;
	token.text = m_input.substr(start, m_pos - start);
	token.number = value;
	return token;
}

std::vector<Token> Lexer::tokenize()
{
	std::vector<Token> tokens;
	while (true)
    {
		skipSpaces();
		if (m_pos >= m_input.size())
        {
			Token endToken;
			endToken.type = TOK_END;
			endToken.text = "";
			endToken.number = 0.0;
			tokens.push_back(endToken);
			break;
		}
		char c = m_input[m_pos];
		if (std::isdigit(static_cast<unsigned char>(c)) || c == '.')
        {
			tokens.push_back(readNumber());
			continue;
		}
		Token token;
		token.text = std::string(1, c);
		token.number = 0.0;
		if (c == '+')
			token.type = TOK_PLUS;
		else if (c == '-')
			token.type = TOK_MINUS;
		else if (c == '*')
			token.type = TOK_STAR;
		else if (c == '^')
			token.type = TOK_CARET;
		else if (c == '=')
			token.type = TOK_EQUAL;
		else if (c == 'X' || c == 'x')
			token.type = TOK_VARIABLE;
		else
			throw ParseError("Unexpected character in input.");
		++m_pos;
		tokens.push_back(token);
	}
	return tokens;
}
