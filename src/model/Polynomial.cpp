#include "Polynomial.hpp"

#include <iomanip>
#include <sstream>

namespace {
	const double kEpsilon = 1e-9;

	double absDouble(double value)
    {
		return value < 0.0 ? -value : value;
	}
	std::string formatCoeff(double value)
    {
		if (absDouble(value) < kEpsilon)
			return "0";
		std::ostringstream out;
		out << std::setprecision(15) << value;
		std::string text = out.str();
		size_t dot = text.find('.');
		if (dot != std::string::npos) {
			while (!text.empty() && text.back() == '0')
				text.pop_back();
			if (!text.empty() && text.back() == '.')
				text.pop_back();
		}
		if (text == "-0")
			return "0";
		return text;
	}
}

void Polynomial::addTerm(int degree, double coeff)
{
	m_coeffs[degree] += coeff;
}

void Polynomial::reduce()
{
	for (std::map<int, double>::iterator it = m_coeffs.begin(); it != m_coeffs.end(); )
    {
		if (absDouble(it->second) < kEpsilon)
			m_coeffs.erase(it++);
		else
			++it;
	}
}

int Polynomial::degree() const
{
	if (m_coeffs.empty())
		return 0;
	return m_coeffs.rbegin()->first;
}

double Polynomial::coeff(int degree) const
{
	std::map<int, double>::const_iterator it = m_coeffs.find(degree);
	if (it == m_coeffs.end())
		return 0.0;
	return it->second;
}

std::string Polynomial::toReducedForm() const
{
	int maxDegree = 0;
	if (!m_coeffs.empty())
		maxDegree = m_coeffs.rbegin()->first;
	std::ostringstream out;
	bool first = true;
	for (int degree = 0; degree <= maxDegree; ++degree)
    {
		double value = coeff(degree);
		if (first)
        {
			out << formatCoeff(value) << " * X^" << degree;
			first = false;
			continue;
		}
		if (value < 0)
			out << " - " << formatCoeff(absDouble(value)) << " * X^" << degree;
		else
			out << " + " << formatCoeff(value) << " * X^" << degree;
	}
	out << " = 0";
	return out.str();
}
