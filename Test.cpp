/*
** EPITECH PROJECT, 2022
** B-CPP-500-PAR-5-1-rtype-zacharie.lawson
** File description:
** Test
*/
#include <string>
#include <iostream>

class Test {
    public:
        Test(std::string str)
        : _str(str)
        {
        }
        ~Test() = default;

    protected:
        std::string _str;
};


class UserTest : public Test {
    public:
        UserTest(std::string str2)
        : Test("Test"), _str2(str2)
        {
        }
        ~UserTest() = default;

        void Start()
        {
            std::cout << this->_str << std::endl << this->_str2 << std::endl;
        }

    protected:
    private:
        std::string _str2;
};

int main()
{
    UserTest ut(std::string("hey"));
    ut.Start();
}