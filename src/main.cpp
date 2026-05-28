#include <iostream>
#include <string>
#include "./parser/Parser.hpp"

void setter(std::string* str, char **av)
{
	parser Parse;
	if (av == NULL)
	{
		Parse.set_all(*str);
		Parse.Parser();
	}
	else if (str == NULL)
	{
		std::string tmp;
		for (int i = 1; av[i]; i++)
			tmp += av[i];
		Parse.set_all(tmp);
		Parse.Parser();
	}
}


int main(int ac, char **av)
{
	parser Parse;    
	if (ac < 2)
	{
		std::string first;
		if (std::getline(std::cin, first))
			setter(&first, NULL);
	}
	else
		setter(NULL, av);
	return (0);
}
