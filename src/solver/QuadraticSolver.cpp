#include "QuadraticSolver.hpp"

void QuadraticSolver::solve(double a, double b, double c)
{
	double discriminant = b * b - 4.0 * a * c;
	if (discriminant > epsilon())
	{
		std::cout << "Discriminant is strictly positive, the two solutions are:" << std::endl;
		double root = sqrtNewton(discriminant);
		double sol1 = (-b - root) / (2.0 * a);
		double sol2 = (-b + root) / (2.0 * a);
		std::cout << formatReal(sol1) << std::endl;
		std::cout << formatReal(sol2) << std::endl;
		return;
	}

	if (absDouble(discriminant) <= epsilon())
	{
		std::cout << "Discriminant is zero, the solution is:" << std::endl;
		double sol = -b / (2.0 * a);
		std::cout << formatReal(sol) << std::endl;
		return;
	}

	std::cout << "Discriminant is strictly negative, the two complex solutions are:" << std::endl;
	double root = sqrtNewton(-discriminant);
	double realPart = -b / (2.0 * a);
	double imagPart = root / (2.0 * a);
	long long aInt = 0;
	long long bInt = 0;
	long long cInt = 0;
	long long rootInt = 0;
	bool useFraction = isNearInt(a, aInt) && isNearInt(b, bInt) && isNearInt(c, cInt) && isNearInt(root, rootInt);
	long long realNum = -bInt;
	long long realDen = 2 * aInt;
	long long imagNum = rootInt;
	long long imagDen = 2 * aInt;
	std::string realText = formatFractionIfPossible(realPart, realNum, realDen, useFraction);
	std::string imagText = formatImaginary(absDouble(imagPart), absLong(imagNum), absLong(imagDen), useFraction);
	std::cout << realText << " + " << imagText << std::endl;
	std::cout << realText << " - " << imagText << std::endl;
}