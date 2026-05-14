#pragma once

#include <iostream>
#include <sstream>
#include <string>

class Solver {
	protected:
		static double epsilon() {
			return 1e-9;
		}

		static double absDouble(double value) {
			return value < 0.0 ? -value : value;
		}

		static long long absLong(long long value) {
			return value < 0 ? -value : value;
		}

		static long long gcdLong(long long a, long long b) {
			a = absLong(a);
			b = absLong(b);
			while (b != 0) {
				long long tmp = a % b;
				a = b;
				b = tmp;
			}
			return a == 0 ? 1 : a;
		}

		static double sqrtNewton(double value) {
			if (value < 0.0) {
				return 0.0;
			}
			if (value == 0.0) {
				return 0.0;
			}
			double x = value;
			double prev = 0.0;
			int iterations = 0;
			while (absDouble(x - prev) > epsilon() && iterations < 1000) {
				prev = x;
				x = 0.5 * (x + value / x);
				++iterations;
			}
			return x;
		}

		static bool isNearInt(double value, long long &out) {
			long long rounded = static_cast<long long>(value + (value >= 0.0 ? 0.5 : -0.5));
			if (absDouble(value - static_cast<double>(rounded)) <= epsilon()) {
				out = rounded;
				return true;
			}
			return false;
		}

		static std::string formatDecimal(double value) {
			std::ostringstream out;
			out << value;
			return out.str();
		}

		static std::string formatFraction(long long num, long long den) {
			if (den < 0) {
				num = -num;
				den = -den;
			}
			long long div = gcdLong(num, den);
			num /= div;
			den /= div;
			if (den == 1) {
				return formatDecimal(static_cast<double>(num));
			}
			std::ostringstream out;
			out << num << '/' << den;
			return out.str();
		}

		static std::string formatReal(double value) {
			long long asInt = 0;
			if (isNearInt(value, asInt)) {
				return formatDecimal(static_cast<double>(asInt));
			}
			return formatDecimal(value);
		}

		static std::string formatFractionIfPossible(double value, long long num, long long den, bool useFraction) {
			if (useFraction) {
				return formatFraction(num, den);
			}
			return formatReal(value);
		}

		static std::string formatImaginary(double value, long long num, long long den, bool useFraction) {
			if (useFraction) {
				if (den < 0) {
					num = -num;
					den = -den;
				}
				long long div = gcdLong(num, den);
				num /= div;
				den /= div;
				std::ostringstream out;
				if (den == 1) {
					out << num << 'i';
					return out.str();
				}
				out << num << 'i' << '/' << den;
				return out.str();
			}
			std::ostringstream out;
			out << value << 'i';
			return out.str();
		}
};

class ConstantSolver : public Solver {
	public:
		static void solve(double c) {
			if (absDouble(c) < epsilon()) {
				std::cout << "Any real number is a solution." << std::endl;
			} else {
				std::cout << "No solution." << std::endl;
			}
		}
};
