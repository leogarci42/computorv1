#include "LinearSolver.hpp"

void LinearSolver::solve(double b, double c)
{
	if (absDouble(b) < epsilon())
	{
		std::cout << "No solution." << std::endl;
		return;
	}
	double solution = -c / b;
	std::cout << "The solution is:" << std::endl;
	std::cout << formatReal(solution) << std::endl;
}