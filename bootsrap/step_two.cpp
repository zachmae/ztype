#include <iostream>
#include <vector>
#include <optional>
#include <any>
#include <string>
#include <unordered_map>
#include <typeindex>
#include <functional>
//#include <map>

//Step 0:
struct entity_t {
    size_t _idx;
    
    entity_t()
    {
        _idx = 0;
    };
    explicit entity_t(size_t idx)
    {
        _idx = idx;
    };
    ~entity_t() = default;

};

// # TEST ENTITY
/*int main()
{
    entity e;
    //entity e2(10);
    return 0;
}*/

// ~ Step 1: 
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

/**
 * @brief class sparce_array
 * @param template <typename Component>
 */
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
        sparse_array(sparse_array const &) = default; // copy constructor
        sparse_array(sparse_array &&) noexcept = default; // move constructor
        ~sparse_array() = default;
        sparse_array &operator=(sparse_array const &) = default; // copy assignment operator
        sparse_array &operator=(sparse_array &&) noexcept = default; // move assignment operator

        reference_type operator[](size_t idx)
        {
            return _data[idx];
        };

        const_reference_type operator[](size_t idx) const
        {
            return _data.at(idx);
        };

        iterator begin() {
            return _data.begin();
        };

        const_iterator begin() const
        {
            return _data.begin();
        };
        const_iterator cbegin() const
        {
            return _data.cbegin();
        };
        iterator end()
        {
            return _data.end();
        };
        const_iterator end() const
        {
            return _data.end();
        };
        const_iterator cend() const
        {
            return _data.cend();
        };
        size_type size() const
        {
            return _data.size();
        };

        //lvalue 
        reference_type insert_at ( size_type pos , Component const &c) //developpez.net/forums/d1821445/c-cpp/cpp/langage/correctement-parcourir-vector-cpp14-plus/
        {   
            if (_data.size() <= pos) 
                _data.resize(pos + 1); 

            _data[pos] = std::make_optional (c);

//            std::cout << _data[pos] << std::endl;

            return _data[pos];
        };
        
        //rvalue
        reference_type insert_at ( size_type pos , Component &&c)
        {
            if (_data.size() <= pos) 
                _data.resize(pos + 1);

            _data[pos] = std::make_optional (std::move(c));

//            std::cout << _data[pos] << std::endl;

            return _data[pos];
        };

        template <class ... Params>
        reference_type emplace_at ( size_type pos , Params &&...args)
        {
            container_t vecArgs = {args...};

            int i = vecArgs.size();
            if ( _data.size() <= pos + i)
                _data.resize(pos + i);
            i = 0;
            for(value_type v : vecArgs) {
                _data[pos + i] = v;
                ++i;
            }
            return _data[pos];
        };

        void erase ( size_type pos ) {
            if (pos < _data.size())
                _data[pos] = std::nullopt;
        };

        size_type get_index ( value_type const &v) const
        {
            for(unsigned int i = 0; i < _data.size(); i++) {
                if (v == _data[i])
                    return i;
            }
            return 0;
        };

        void display() const
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

// # TEST SPARSE_ARRAY
/*int main(int argc, char const *argv[])
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
}*/


// ~ Step 2.: REGISTRY
    // ~ the goal is to store SparseArray in a container.

// ~ Step 2.0: TYPES AS INDICES
    // ~ std::type_index (to create a unique index inside an associativecontainer, that use the actual type of an object.).
    // ~ std::(unordered_)map

// ~ Step 2.1: STORING MULTIPLE TYPES IN A CONTAINER
    // ~ type:"std::any"
    // ~ cast:"std::any_cast" (The cast will fail and an exception will be raised in case the destination type is not compatible with the stored object.)

// ~ Step 2.2: WRITING THE REGISTRY
    // ~ register_components adds a new component array to our associative container.
    // ~ get_components are functions to retrieve the array that stores a specific type of components.
    // ~ You have to write these functions such that the index of an array is made using std::type_index, and the
    // ~ std::any_cast is made by the registry instead the system that will use the sparse_arrays.

/**
 * @brief class registry
 * @param template <typename Component>
 */
class registry {
    public :
        template <class Component>
        sparse_array<Component> &register_component()
        {
            // ~ add a sparse_array<Component> to our registry.
            _components_arrays[std::type_index(typeid(Component))] = std::make_any<sparse_array<Component>>();

            return std::any_cast<sparse_array<Component> &>(_components_arrays[std::type_index(typeid(Component))]);
        };
        
        template <class Component>
        sparse_array<Component> &get_components()
        {
            return std::any_cast<sparse_array<Component> &>(_components_arrays[std::type_index(typeid(Component))]); //
        };

        template <class Component>
        sparse_array<Component> const &get_components () const //the last const means that the function can't modify variable(s) of the class
        {
            return std::any_cast<sparse_array<Component> &>(_components_arrays.at(std::type_index(typeid(Component))));
        };

    private :
        std::unordered_map<std::type_index, std::any> _components_arrays;
};

// # TEST REGISTERY 2.2
int main(int argc, char const *argv[])
{
    registry reg;
    reg.register_component<float>();
    reg.register_component<int>();
    reg.register_component<std::string>();
    reg.get_components<float>().emplace_at(1, 1.0f, 2.0f);
    reg.get_components<float>().display();
    reg.get_components<int>().display();
}


//Step 3.0: USING THE ECS 

//Step 3.1: COMPONENTS LIST

//Step 3.2: SYSTEMS

//Step 3.3: WRAPPING IT ALL TOGETHER

//Step 4 GOING FURTHER

//Step 4.1: MOVING SYSTEMS INSIDE THE REGISTRY

//Step 4.2: CONTAINER ADAPTOR AND CUSTOM ITERATOR

//Step 4.3: OPTIMIZING MEMORY FOOTPRINT

// * use (std::variant and std::visit)
