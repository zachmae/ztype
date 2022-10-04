#include <iostream>

#ifndef STEP_ZERO_H
#define STEP_ZERO_H

class entity {
    public:
        size_t _size;
        
        entity() { std::cout << "test" << std::endl; };
        explicit entity(size_t size);
        ~entity() = default;
        //inline getSize() const { return _size; };

    protected:
    private:

};

#endif // STEP_ZERO_H

int main()
{
    entity e;
    //entity e2(10);
    return 0;
}