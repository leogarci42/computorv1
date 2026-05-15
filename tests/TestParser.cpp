#include <iostream>
#include <sstream>
#include <string>

#include "../src/parser/Parser.hpp"

int runLexerTests();
int runSolverTests();

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

	std::string captureParserOutput(const std::string &input)
	{
		parser parse;
		parse.set_all(input);
		std::ostringstream out;
		std::streambuf *oldBuf = std::cout.rdbuf(out.rdbuf());
		parse.Parser();
		std::cout.rdbuf(oldBuf);
		return out.str();
	}
}

static int runParserTests()
{
	int failures = 0;

	{
		int failuresBefore = failures;
		printCaseHeader("Quadratic input parses");
		std::string output = captureParserOutput("2 * X^2 + 1 = 12");
		std::cout << output;
		failures += expect(output.find("Parse error") == std::string::npos, "Quadratic input should parse");
		failures += expect(output.find("Polynomial degree: 2") != std::string::npos, "Quadratic degree detection");
		printCaseResult(failuresBefore, failures);
	}

	{
		int failuresBefore = failures;
		printCaseHeader("Implicit coefficients");
		std::string output = captureParserOutput("X^2 + X + 1 = 0");
		std::cout << output;
		failures += expect(output.find("Parse error") == std::string::npos, "Implicit coefficients should parse");
		failures += expect(output.find("Polynomial degree: 2") != std::string::npos, "Implicit degree detection");
		printCaseResult(failuresBefore, failures);
	}

	{
		int failuresBefore = failures;
		printCaseHeader("Lowercase variable parses");
		std::string output = captureParserOutput("x^2 - 3x + 2 = 0");
		std::cout << output;
		failures += expect(output.find("Parse error") == std::string::npos, "Lowercase variable should parse");
		failures += expect(output.find("Polynomial degree: 2") != std::string::npos, "Lowercase degree detection");
		printCaseResult(failuresBefore, failures);
	}

	{
		int failuresBefore = failures;
		printCaseHeader("Linear equation parses");
		std::string output = captureParserOutput("2*X - 4 = 0");
		std::cout << output;
		failures += expect(output.find("Parse error") == std::string::npos, "Linear input should parse");
		failures += expect(output.find("Polynomial degree: 1") != std::string::npos, "Linear degree detection");
		printCaseResult(failuresBefore, failures);
	}

	{
		int failuresBefore = failures;
		printCaseHeader("Constant equation parses");
		std::string output = captureParserOutput("2 = 2");
		std::cout << output;
		failures += expect(output.find("Parse error") == std::string::npos, "Constant input should parse");
		failures += expect(output.find("Polynomial degree: 0") != std::string::npos, "Constant degree detection");
		printCaseResult(failuresBefore, failures);
	}

	{
		int failuresBefore = failures;
		printCaseHeader("Non-integer exponent fails");
		std::string output = captureParserOutput("X^2.5 = 0");
		std::cout << output;
		failures += expect(output.find("Parse error") != std::string::npos, "Non-integer exponent should fail");
		printCaseResult(failuresBefore, failures);
	}

	{
		int failuresBefore = failures;
		printCaseHeader("Missing equal sign fails");
		std::string output = captureParserOutput("X^2 + 1");
		std::cout << output;
		failures += expect(output.find("Parse error") != std::string::npos, "Missing '=' should fail");
		printCaseResult(failuresBefore, failures);
	}

	{
		int failuresBefore = failures;
		printCaseHeader("Zero polynomial reduces to degree 0");
		std::string output = captureParserOutput("0*X^2 + 0*X + 0 = 0");
		std::cout << output;
		failures += expect(output.find("Parse error") == std::string::npos, "Zero polynomial should parse");
		failures += expect(output.find("Polynomial degree: 0") != std::string::npos, "Zero polynomial degree");
		printCaseResult(failuresBefore, failures);
	}

	{
		int failuresBefore = failures;
		printCaseHeader("Higher degree parses");
		std::string output = captureParserOutput("X^3 = 0");
		std::cout << output;
		failures += expect(output.find("Parse error") == std::string::npos, "Degree 3 should parse");
		failures += expect(output.find("Polynomial degree: 3") != std::string::npos, "Degree 3 detection");
		printCaseResult(failuresBefore, failures);
	}

	{
		int failuresBefore = failures;
		printCaseHeader("Zero exponent treated as constant");
		std::string output = captureParserOutput("X^0 = 1");
		std::cout << output;
		failures += expect(output.find("Parse error") == std::string::npos, "Zero exponent should parse");
		failures += expect(output.find("Polynomial degree: 0") != std::string::npos, "Zero exponent degree");
		printCaseResult(failuresBefore, failures);
	}

	{
		int failuresBefore = failures;
		printCaseHeader("Missing variable after star fails");
		std::string output = captureParserOutput("2* = 0");
		std::cout << output;
		failures += expect(output.find("Parse error") != std::string::npos, "Missing variable after '*' should fail");
		printCaseResult(failuresBefore, failures);
	}

	{
		int failuresBefore = failures;
		printCaseHeader("Star after variable fails");
		std::string output = captureParserOutput("X*2 = 0");
		std::cout << output;
		failures += expect(output.find("Parse error") != std::string::npos, "Star after variable should fail");
		printCaseResult(failuresBefore, failures);
	}

	{
		int failuresBefore = failures;
		printCaseHeader("Negative exponent fails");
		std::string output = captureParserOutput("X^-1 = 0");
		std::cout << output;
		failures += expect(output.find("Parse error") != std::string::npos, "Negative exponent should fail");
		printCaseResult(failuresBefore, failures);
	}

	{
		int failuresBefore = failures;
		printCaseHeader("Invalid term reports error");
		std::string output = captureParserOutput("2 * 1 = 12");
		std::cout << output;
		failures += expect(output.find("Parse error") != std::string::npos, "Invalid term should report parse error");
		printCaseResult(failuresBefore, failures);
	}

	if (failures == 0)
		std::cout << kGreen << "[PASS] Parser tests" << kReset << std::endl;
	return failures;
}

int main()
{
	int failures = 0;
	failures += runLexerTests();
	failures += runParserTests();
	failures += runSolverTests();
	if (failures == 0)
		std::cout << kGreen << "[PASS] All tests" << kReset << std::endl;
	return failures == 0 ? 0 : 1;
}
