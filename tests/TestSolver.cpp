#include <iostream>
#include <sstream>
#include <string>

#include "../src/solver/LinearSolver.hpp"
#include "../src/solver/QuadraticSolver.hpp"
#include "../src/solver/Solver.hpp"

namespace
{
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

	std::string captureOutput(void (*fn)())
	{
		std::ostringstream out;
		std::streambuf *oldBuf = std::cout.rdbuf(out.rdbuf());
		fn();
		std::cout.rdbuf(oldBuf);
		return out.str();
	}
}

int runSolverTests()
{
	int failures = 0;

	{
		int failuresBefore = failures;
		printCaseHeader("Linear solver: 2x - 4 = 0");
		std::string output = captureOutput([]() { LinearSolver::solve(2.0, -4.0); });
		std::cout << output;
		failures += expect(output.find("The solution is:") != std::string::npos, "Linear solver banner");
		failures += expect(output.find("2") != std::string::npos, "Linear solver solution value");
		printCaseResult(failuresBefore, failures);
	}

	{
		int failuresBefore = failures;
		printCaseHeader("Linear solver: 0x + 2 = 0");
		std::string output = captureOutput([]() { LinearSolver::solve(0.0, 2.0); });
		std::cout << output;
		failures += expect(output.find("No solution") != std::string::npos, "Linear solver no solution");
		printCaseResult(failuresBefore, failures);
	}

	{
		int failuresBefore = failures;
		printCaseHeader("Linear solver: -4x + 2 = 0");
		std::string output = captureOutput([]() { LinearSolver::solve(-4.0, 2.0); });
		std::cout << output;
		failures += expect(output.find("The solution is:") != std::string::npos, "Linear solver banner");
		failures += expect(output.find("0.5") != std::string::npos, "Linear solver fractional solution");
		printCaseResult(failuresBefore, failures);
	}

	{
		int failuresBefore = failures;
		printCaseHeader("Linear solver: 3x + 1 = 0");
		std::string output = captureOutput([]() { LinearSolver::solve(3.0, 1.0); });
		std::cout << output;
		failures += expect(output.find("The solution is:") != std::string::npos, "Linear solver banner");
		failures += expect(output.find("-0.33") != std::string::npos || output.find("-0.3") != std::string::npos, "Linear solver decimal solution");
		printCaseResult(failuresBefore, failures);
	}

	{
		int failuresBefore = failures;
		printCaseHeader("Quadratic solver: x^2 + 2x + 1 = 0");
		std::string output = captureOutput([]() { QuadraticSolver::solve(1.0, 2.0, 1.0); });
		std::cout << output;
		failures += expect(output.find("Discriminant is zero") != std::string::npos, "Quadratic solver discriminant zero");
		failures += expect(output.find("-1") != std::string::npos, "Quadratic solver root value");
		printCaseResult(failuresBefore, failures);
	}

	{
		int failuresBefore = failures;
		printCaseHeader("Quadratic solver: x^2 - 1 = 0");
		std::string output = captureOutput([]() { QuadraticSolver::solve(1.0, 0.0, -1.0); });
		std::cout << output;
		failures += expect(output.find("Discriminant is strictly positive") != std::string::npos, "Quadratic solver discriminant positive");
		failures += expect(output.find("1") != std::string::npos, "Quadratic solver positive root");
		failures += expect(output.find("-1") != std::string::npos, "Quadratic solver negative root");
		printCaseResult(failuresBefore, failures);
	}

	{
		int failuresBefore = failures;
		printCaseHeader("Quadratic solver: 2x^2 - 8 = 0");
		std::string output = captureOutput([]() { QuadraticSolver::solve(2.0, 0.0, -8.0); });
		std::cout << output;
		failures += expect(output.find("Discriminant is strictly positive") != std::string::npos, "Quadratic solver discriminant positive");
		failures += expect(output.find("2") != std::string::npos, "Quadratic solver root magnitude");
		printCaseResult(failuresBefore, failures);
	}

	{
		int failuresBefore = failures;
		printCaseHeader("Quadratic solver: x^2 + 1 = 0");
		std::string output = captureOutput([]() { QuadraticSolver::solve(1.0, 0.0, 1.0); });
		std::cout << output;
		failures += expect(output.find("Discriminant is strictly negative") != std::string::npos, "Quadratic solver discriminant negative");
		failures += expect(output.find("i") != std::string::npos, "Quadratic solver imaginary output");
		printCaseResult(failuresBefore, failures);
	}

	{
		int failuresBefore = failures;
		printCaseHeader("Quadratic solver: x^2 + 2x + 5 = 0");
		std::string output = captureOutput([]() { QuadraticSolver::solve(1.0, 2.0, 5.0); });
		std::cout << output;
		failures += expect(output.find("Discriminant is strictly negative") != std::string::npos, "Quadratic solver negative discriminant");
		failures += expect(output.find("2i") != std::string::npos, "Quadratic solver imaginary magnitude");
		printCaseResult(failuresBefore, failures);
	}

	{
		int failuresBefore = failures;
		printCaseHeader("Constant solver: 0 = 0");
		std::string output = captureOutput([]() { ConstantSolver::solve(0.0); });
		std::cout << output;
		failures += expect(output.find("Any real number") != std::string::npos, "Constant solver infinite solutions");
		printCaseResult(failuresBefore, failures);
	}

	{
		int failuresBefore = failures;
		printCaseHeader("Constant solver: 2 = 0");
		std::string output = captureOutput([]() { ConstantSolver::solve(2.0); });
		std::cout << output;
		failures += expect(output.find("No solution") != std::string::npos, "Constant solver no solution");
		printCaseResult(failuresBefore, failures);
	}

	if (failures == 0)
		std::cout << kGreen << "[PASS] Solver tests" << kReset << std::endl;
	return failures;
}
