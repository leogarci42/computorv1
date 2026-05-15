#include "Parser.hpp"

#include <iostream>

#include "../utils/Exceptions.hpp"
#include "../solver/LinearSolver.hpp"
#include "../solver/QuadraticSolver.hpp"
#include "../solver/Solver.hpp"

namespace {
	const double kEpsilon = 1e-9;

	double absDouble(double value)
	{
		return value < 0.0 ? -value : value;
	}

	bool isNearInt(double value, long long &out)
	{
		long long rounded = static_cast<long long>(value + (value >= 0.0 ? 0.5 : -0.5));
		if (absDouble(value - static_cast<double>(rounded)) <= kEpsilon)
		{
			out = rounded;
			return true;
		}
		return false;
	}

	void addTerm(Polynomial &poly, int degree, double coeff)
	{
		if (absDouble(coeff) < kEpsilon)
			return;
		poly.addTerm(degree, coeff);
	}

}


const Token &parser::peek() const
{
	return m_tokens[m_pos];
}

const Token &parser::advance()
{
	return m_tokens[m_pos++];
}

bool parser::match(TokenType type)
{
	if (peek().type == type)
	{
		++m_pos;
		return true;
	}
	return false;
}

void parser::parseTerm(int sideSign, Polynomial &poly)
{
	int sign = 1;
	if (match(TOK_PLUS))
		sign = 1;
	else if (match(TOK_MINUS))
		sign = -1;
	bool hasCoeff = false;
	double coeff = 1.0;
	if (peek().type == TOK_NUMBER)
	{
		coeff = advance().number;
		hasCoeff = true;
	}
	bool sawStar = false;
	if (match(TOK_STAR))
	{
		if (!hasCoeff)
			throw ParseError("Missing coefficient before '*'.");
		sawStar = true;
	}
	bool hasVar = false;
	int degree = 0;
	if (match(TOK_VARIABLE))
	{
		hasVar = true;
		degree = 1;
		if (match(TOK_CARET))
		{
			if (peek().type != TOK_NUMBER)
				throw ParseError("Missing exponent after '^'.");
			double expValue = advance().number;
			long long expInt = 0;
			if (!isNearInt(expValue, expInt) || expInt < 0)
				throw ParseError("Exponent must be a non-negative integer.");
			degree = static_cast<int>(expInt);
		}
	}
	else if (sawStar)
		throw ParseError("Expected variable after '*'.");
	if (!hasVar && !hasCoeff)
		throw ParseError("Invalid term.");
	if (!hasVar)
		degree = 0;
	addTerm(poly, degree, coeff * sign * sideSign);
}

void parser::parseSide(int sideSign, Polynomial &poly)
{
	while (peek().type != TOK_EQUAL && peek().type != TOK_END)
	{
		parseTerm(sideSign, poly);
		if (peek().type == TOK_PLUS || peek().type == TOK_MINUS)
			continue ;
		if (peek().type == TOK_EQUAL || peek().type == TOK_END)
			break ;
		std::cerr << peek().type << std::endl;
		throw ParseError("Unexpected token in equation.");
	}
}

Polynomial parser::parseEquation()
{
	Lexer lexer(get_all());
	m_tokens = lexer.tokenize();
	m_pos = 0;
	Polynomial poly;
	parseSide(1, poly);
	if (!match(TOK_EQUAL))
		throw ParseError("Missing '=' in equation.");
	parseSide(-1, poly);
	if (peek().type != TOK_END)
		throw ParseError("Unexpected token after equation.");
	poly.reduce();
	return poly;
}

void parser::Parser()
{
	try
	{
		Polynomial poly = parseEquation();
		std::cout << "Reduced form: " << poly.toReducedForm() << std::endl;
		std::cout << "Polynomial degree: " << poly.degree() << std::endl;
		int deg = poly.degree();
		double a = poly.coeff(2);
		double b = poly.coeff(1);
		double c = poly.coeff(0);
		if (deg == 0)
			ConstantSolver::solve(c);
		else if (deg == 1)
			LinearSolver::solve(b, c);
		else if (deg == 2)
			QuadraticSolver::solve(a, b, c);
		else
			std::cout << "The polynomial degree is strictly greater than 2, I can't solve." << std::endl;
	}
	catch (const ParseError &err) {
		std::cout << "Parse error: " << err.what() << std::endl;
	}
}
