#pragma once

#include <map>
#include <string>

class Polynomial {
	public:
		void addTerm(int degree, double coeff);
		void reduce();
		int degree() const;
		double coeff(int degree) const;
		std::string toReducedForm() const;
	private:
		std::map<int, double> m_coeffs;
};
