#pragma once

#include "Solver.hpp"

class LinearSolver : public Solver {
	public:
		static void solve(double b, double c);
};
