/*
** EPITECH PROJECT, 2022
** epi_github3
** File description:
** lambda
*/

#include <iostream>

std::ostream operator<<(std::ostream &os, const std::any &a)
{
    if (a.has_value()) {
        if (a.type() == typeid(int)) {
            os << std::any_cast<int>(a);
        } else if (a.type() == typeid(unsigned)) {
            os << std::any_cast<unsigned>(a);
        } else if (a.type() == typeid(float)) {
            os << std::any_cast<float>(a);
        } else if (a.type() == typeid(double)) {
            os << std::any_cast<double>(a);
        } else if (a.type() == typeid(char const*)) {
            os << std::quoted(std::any_cast<char const*>(a));
        } else {
            os << "???";
        }
    } else {
        os << "{}";
    }
    return os;
}

template <class F>

std::pair<int, std::string> function(F const &f)
{
    return {
        5,
        f(5)
    };
}

void test(char **av) {
    std::string str(av[1]);

}

void test0(int num) {
    std::cout << num << std::endl;
}

int main(int ac, char **av)
{
    std::pair<int, std::string> p;
    if (ac == 0)
        return 0;
    p = function([](int x) -> std::string { 
        std::string a("end");
        for (int y = x; y >= 0;--y) {
            std::cout << y;
            (y != 0) ? std::cout << ", " : std::cout << std::endl;
                if (y % 2 == 1) {
                    std::string("odd");
                } else {
                    std::string("even");
                }
            }
        return a;
    }
    );
    std::cout << p;
    return 0;
}