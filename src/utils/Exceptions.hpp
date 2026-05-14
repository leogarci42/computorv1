#pragma once

#include <stdexcept>

class ParseError : public std::runtime_error {
	public:
		explicit ParseError(const std::string &message) : std::runtime_error(message) {}
};
