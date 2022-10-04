#include <iostream>
#include <vector>
#include <optional>

template <typename Component> // You can also mirror the definition of std :: vector , that takes an additional allocator .

std::ostream& operator<<(std::ostream& os, std::optional<Component> const &c)
{
//    std::string a("a");
//    os << a.str();
    if (c)
        os << c.value(); //any need to try type int str or float or else
    else
        os << "None";
    return os;
}

template <typename Component> // You can also mirror the definition of std :: vector , that takes an additional allocator .

class sparse_array {

    public :
        using value_type = std::optional<Component>; // optional component type
        using reference_type = value_type &;
        using const_reference_type = value_type const &;
        using container_t = std::vector<value_type>; // optionally add your allocator template here .
        using size_type = typename container_t::size_type ;
        using iterator = typename container_t::iterator ;
        using const_iterator = typename container_t::const_iterator ;

    public :
        sparse_array() = default; // You can add more constructors .
        sparse_array(sparse_array const &); // copy constructor
        sparse_array(sparse_array &&) noexcept; // move constructor
        ~sparse_array() = default;
        sparse_array &operator=(sparse_array const &); // copy assignment operator
        sparse_array &operator=(sparse_array &&) noexcept; // move assignment operator
        reference_type operator[](size_t idx);
        const_reference_type operator[](size_t idx) const;
        iterator begin();
        const_iterator begin() const;
        const_iterator cbegin() const;
        iterator end();
        const_iterator end() const;
        const_iterator cend() const;
        size_type size() const;

        //lvalue 
        inline reference_type insert_at ( size_type pos , Component const &c) //developpez.net/forums/d1821445/c-cpp/cpp/langage/correctement-parcourir-vector-cpp14-plus/
        {   
            if (_data.size() <= pos) 
                _data.resize(pos + 1); 

            _data[pos] = std::make_optional (c);

//            std::cout << _data[pos] << std::endl;

            return _data[pos];
        };
        
        //rvalue
        inline reference_type insert_at(size_type pos, Component &&c)
        {
            if (_data.size() <= pos) 
                _data.resize(pos + 1);

            _data[pos] = std::make_optional (std::move(c));

//            std::cout << _data[pos] << std::endl;

            return _data[pos];
        };

        template <class ... Params>
        inline reference_type emplace_at ( size_type pos , Params &&...args)
        {
            container_t vecArgs = {args...};
            int i = 0;

            for(value_type v : vecArgs)
                ++i;
            if ( _data.size() <= pos + i)
                _data.resize(pos + i);
            i = 0;
            for(value_type v : vecArgs) {
                _data[pos + i] = v;
                ++i;
            }
            return _data[pos];
        };

        inline void erase ( size_type pos ) {
            if (pos < _data.size())
                _data[pos] = std::nullopt;
        };

        inline size_type get_index ( value_type const &v) const
        {
            for(unsigned int i = 0; i < _data.size(); i++) {
                if (v == _data[i])
                    return i;
            }
            return 0;
        };

        inline void display() const
        {
            std::cout << "{ ";
            for (auto const &v : _data) {
                std::cout << v << " ";
            }   
            std::cout << "}" << std::endl;
        };

    private :
        container_t _data ;
};

int main(int argc, char const *argv[])
{
    sparse_array<int> test;
    int i = 8;

    test.emplace_at(1, 1, 2, 4, 5);
    test.display();
    std::cout << test.get_index(1) << std::endl;
    test.insert_at(0, i);
    test.display();
    test.insert_at(1, 7);
    test.display();
    test.erase(0);
    test.erase(1);
    test.display();
    return 0;
}

