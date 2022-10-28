#include <iostream>

class IAnimal {
    public:
        virtual void sound(std::string) = 0;
        void getAge(void) {
            std::cout << "Animal??: Age is " << _age << std::endl;
        }
    protected:
        int _age;
};

class Lion : public IAnimal {
    public:
        Lion() = default;
        Lion(int age) { _age = age; };
        ~Lion() = default;
        void sound(std::string sound) {
            std::cout << "roar: " << sound << std::endl;
        }
        void bite(void) {
            std::cout << "Archhkrkrrr" << std::endl;
        }
};

class Chien: public Lion {
    public:
        Chien() = default;
        Chien(int age) { _age = (age * 2); std::cout << "AGGGGHGGGGGGGGG" << std::endl;};
        ~Chien() = default;
        void sound(std::string sound) {
            std::cout << "roaf: " << sound << std::endl;
        };
};

class Chat : public IAnimal {
    public:
        Chat(int age) { _age = age; }
        ~Chat() = default;
        void sound(std::string sound) {
            std::cout << "meow: " << sound << std::endl;
        }
        void getAge(void) {
            std::cout << "Chat: Age is " << _age << std::endl;
        }
};

void function(IAnimal &s)
{
    s.sound("");
}

int main()
{
    Lion lion2;
    lion2.getAge();
    Lion lion(10);
    lion.sound("roar");
    lion.getAge();
    lion.bite();
    Chien chien(5);
    chien.sound("woof");
    chien.getAge();
    chien.bite();
    Chat chat(1);
    chat.sound("meow");
    chat.getAge();
    function(lion);
    function(chien);
    function(chat);
    return 0;
}