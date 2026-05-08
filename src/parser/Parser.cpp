#include "Parser.hpp"

void parser::Parser()
{
	std::string all = get_all();
	int t_count = 0;

	for (int i = 0; all[i]; i++)
	{
		if (!std::isspace((int)all[i]))
		{
			val[t_count] += all[i];
		}
		else
			t_count++;
	}
}
