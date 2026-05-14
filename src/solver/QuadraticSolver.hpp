#pragma once

#include "Solver.hpp"

class QuadraticSolver : public Solver {
	public:
		static void solve(double a, double b, double c);
};
