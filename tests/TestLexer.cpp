#include <iostream>
#include <string>
#include <vector>

#include "../src/parser/Lexer.hpp"
#include "../src/utils/Exceptions.hpp"

namespace {
	const char *kGreen = "\033[32m";
	const char *kRed = "\033[31m";
	const char *kBlue = "\033[34m";
	const char *kReset = "\033[0m";

	void printCaseHeader(const std::string &name)
	{
		std::cout << kBlue << "[CASE] " << kReset << name << std::endl;
	}

	void printCaseResult(int failuresBefore, int failuresAfter)
	{
		if (failuresAfter == failuresBefore)
			std::cout << kGreen << "[PASS]" << kReset << std::endl;
	}

	int expect(bool condition, const std::string &message)
	{
		if (!condition)
		{
			std::cout << kRed << "[FAIL] " << kReset << message << std::endl;
			return 1;
		}
		return 0;
	}
}

int runLexerTests()
{
	int failures = 0;

	{
		int failuresBefore = failures;
		printCaseHeader("Tokenize quadratic expression");
		Lexer lexer("2 * X^2 + 1 = 12");
		std::vector<Token> tokens = lexer.tokenize();
		std::vector<TokenType> expected;
		expected.push_back(TOK_NUMBER);
		expected.push_back(TOK_STAR);
		expected.push_back(TOK_VARIABLE);
		expected.push_back(TOK_CARET);
		expected.push_back(TOK_NUMBER);
		expected.push_back(TOK_PLUS);
		expected.push_back(TOK_NUMBER);
		expected.push_back(TOK_EQUAL);
		expected.push_back(TOK_NUMBER);
		expected.push_back(TOK_END);
		failures += expect(tokens.size() == expected.size(), "Token count for quadratic input");
		for (size_t i = 0; i < tokens.size() && i < expected.size(); ++i)
		{
			failures += expect(tokens[i].type == expected[i], "Token type mismatch at position " + std::to_string(i));
		}
		printCaseResult(failuresBefore, failures);
	}

	{
		int failuresBefore = failures;
		printCaseHeader("Lowercase variable token");
		Lexer lexer("x");
		std::vector<Token> tokens = lexer.tokenize();
		failures += expect(tokens.size() == 2, "Lowercase variable token count");
		if (tokens.size() >= 1)
			failures += expect(tokens[0].type == TOK_VARIABLE, "Lowercase variable token type");
		printCaseResult(failuresBefore, failures);
	}

	{
		int failuresBefore = failures;
		printCaseHeader("Implicit multiplication tokenization");
		Lexer lexer("2X + 3x");
		std::vector<Token> tokens = lexer.tokenize();
		failures += expect(tokens.size() == 6, "Implicit multiplication token count");
		if (tokens.size() >= 5)
		{
			failures += expect(tokens[0].type == TOK_NUMBER, "Implicit multiplication first token");
			failures += expect(tokens[1].type == TOK_VARIABLE, "Implicit multiplication second token");
			failures += expect(tokens[2].type == TOK_PLUS, "Implicit multiplication plus token");
			failures += expect(tokens[3].type == TOK_NUMBER, "Implicit multiplication third token");
			failures += expect(tokens[4].type == TOK_VARIABLE, "Implicit multiplication fourth token");
		}
		printCaseResult(failuresBefore, failures);
	}

	{
		int failuresBefore = failures;
		printCaseHeader("Decimal number parsing");
		Lexer lexer(".5 * X = 1");
		std::vector<Token> tokens = lexer.tokenize();
		failures += expect(tokens.size() == 6, "Decimal number token count");
		if (!tokens.empty())
		{
			failures += expect(tokens[0].type == TOK_NUMBER, "Decimal number token type");
			failures += expect(tokens[0].number > 0.49 && tokens[0].number < 0.51, "Decimal number value");
		}
		printCaseResult(failuresBefore, failures);
	}

	{
		int failuresBefore = failures;
		printCaseHeader("Whitespace handling");
		Lexer lexer("  X  ^  2  ");
		std::vector<Token> tokens = lexer.tokenize();
		failures += expect(tokens.size() == 4, "Whitespace token count");
		if (tokens.size() >= 3)
		{
			failures += expect(tokens[0].type == TOK_VARIABLE, "Whitespace variable token");
			failures += expect(tokens[1].type == TOK_CARET, "Whitespace caret token");
			failures += expect(tokens[2].type == TOK_NUMBER, "Whitespace number token");
		}
		printCaseResult(failuresBefore, failures);
	}

	{
		int failuresBefore = failures;
		printCaseHeader("Negative number tokenization");
		Lexer lexer("-3.25 + 2");
		std::vector<Token> tokens = lexer.tokenize();
		failures += expect(tokens.size() == 5, "Negative number token count");
		if (tokens.size() >= 3)
		{
			failures += expect(tokens[0].type == TOK_MINUS, "Negative number minus token");
			failures += expect(tokens[1].type == TOK_NUMBER, "Negative number value token");
			failures += expect(tokens[1].number > 3.24 && tokens[1].number < 3.26, "Negative number absolute value");
		}
		printCaseResult(failuresBefore, failures);
	}

	{
		int failuresBefore = failures;
		printCaseHeader("Integer with trailing dot");
		Lexer lexer("1. * X");
		std::vector<Token> tokens = lexer.tokenize();
		failures += expect(tokens.size() == 5, "Trailing dot token count");
		if (tokens.size() >= 1)
			failures += expect(tokens[0].type == TOK_NUMBER, "Trailing dot token type");
		printCaseResult(failuresBefore, failures);
	}

	{
		int failuresBefore = failures;
		printCaseHeader("Large exponent tokenization");
		Lexer lexer("X^10 = 0");
		std::vector<Token> tokens = lexer.tokenize();
		failures += expect(tokens.size() == 5, "Large exponent token count");
		if (tokens.size() >= 3)
		{
			failures += expect(tokens[0].type == TOK_VARIABLE, "Large exponent variable token");
			failures += expect(tokens[1].type == TOK_CARET, "Large exponent caret token");
			failures += expect(tokens[2].type == TOK_NUMBER, "Large exponent number token");
		}
		printCaseResult(failuresBefore, failures);
	}

	{
		int failuresBefore = failures;
		printCaseHeader("Single dot is invalid");
		bool threw = false;
		try
		{
			Lexer lexer(".");
			lexer.tokenize();
		}
		catch (const ParseError &)
		{
			threw = true;
		}
		failures += expect(threw, "Single dot should throw ParseError");
		printCaseResult(failuresBefore, failures);
	}

	{
		int failuresBefore = failures;
		printCaseHeader("Unsupported exponent format");
		bool threw = false;
		try
		{
			Lexer lexer("1e3 * X = 0");
			lexer.tokenize();
		}
		catch (const ParseError &)
		{
			threw = true;
		}
		failures += expect(threw, "Scientific notation should throw ParseError");
		printCaseResult(failuresBefore, failures);
	}

	{
		int failuresBefore = failures;
		printCaseHeader("Invalid character throws");
		bool threw = false;
		try
		{
			Lexer lexer("2 & X = 0");
			lexer.tokenize();
		}
		catch (const ParseError &)
		{
			threw = true;
		}
		failures += expect(threw, "Invalid character should throw ParseError");
		printCaseResult(failuresBefore, failures);
	}

	if (failures == 0)
		std::cout << kGreen << "[PASS] Lexer tests" << kReset << std::endl;
	return failures;
}
