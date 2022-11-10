/*
** EPITECH PROJECT, 2022
** B-CPP-500-PAR-5-1-rtype-zacharie.lawson
** File description:
** Test
*/

#include <iostream>
#include <any>
#include <vector>
#include <cstring>

class Test;

class Test {
    public:
        Test()
        : pos(0)
        {
        }

        ~Test() = default;

        template<typename Key>
        friend Test &operator<<(Test &t, Key &var)
        {
            size_t size = t.packets.size();
            t.packets.resize(size + sizeof(Key));
            memcpy(t.packets.data() + size, &var, sizeof(Key));

            return t;
        }

        template<typename Key>
        friend Test &operator<<(Test &t, Key &&var)
        {
            size_t size = t.packets.size();
            t.packets.resize(size + sizeof(Key));
            memcpy(t.packets.data() + size, &var, sizeof(Key));

            return t;
        }


        template<typename Key>
        friend Test &operator>>(Test &t, Key &var)
        {
            memcpy(&var, t.packets.data() + t.pos, sizeof(Key));
            t.pos += sizeof(Key);

            return t;
        }

        std::any &my_popback(std::vector<std::any> &vec)
        {
            std::any &tmp = vec.back();
            vec.pop_back();
            return tmp;
        }

        size_t pos;
        std::vector<char> packets;
};

std::ostream &operator <<(std::ostream &os, const Test &t) {
    for(auto &i : t.packets)
        os << std::any_cast<int>(i) << std::endl;
    return os;
}

int main()
{
    Test test;
    int a = 1;
    char b[5] = {'H', 'e', 'l','l','o'};
    int rA{};
    char rB[5] {};
    test << a << b;
    test >> rA >> rB;
    std::cout << rA << " " << rB << std::endl;
    return 0;
}


///////////////////////////////////////////////////////////////////////////////////////////////

/*template<typename Key>
class Test {
    public:
        Test()
        {

        }
        ~Test();

        friend Test<Key> &operator<<(Test<Key> &t, Key &var)
        {
            t.packets.push_back(std::make_any<Key>(var));

            return t;
        }

        friend Test<Key> &operator>>(Test<Key> &t, Key &var)
        {
            var = std::any_cast<Key>(my_popback(packets));

            return t;
        }

        std::any my_popback(std::vector<std::any> packets)
        {
            std::any &tmp = packets.back();
            packets.pop_back();
            return tmp;
        }

        std::vector<std::any> packets;
};

int main()
{
    Test<int> test;
    int a = 1;
    int b{};
    test << a;
    test >> b;
    std::cout << b << std::endl;
    return 0;
}*/



//    <<(params = int)
//int -> packet -> int;
//              >> (params = int)