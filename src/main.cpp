#include <iostream>
#include <string>

int main(int ac, char **av)
{
    (void)av;
    if (ac < 2)
    {
        std::string first;
        if (std::getline(std::cin, first))
            std::cout << first << '\n';
    }
    std::cout << av[1] << std::endl;
    return (0);
}
