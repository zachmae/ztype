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
class registry;

struct entity_t {
    size_t _idx;
    ~entity_t() = default;

    friend registry;

    private:

        explicit entity_t(size_t idx)
        {
            _idx = idx;
        };

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
            bool b = false;
            std::cout << "{ ";
            for (auto const &v : _data) {
                if (b == true)
                    std::cout << ", " << v;
                else
                    std::cout << v;

                b = true;
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

            // ~ add a remove function by entities to our registry. [don't remember?] (args of the lambda) { what the lambda does }
            _components_removes.push_back(
                [] (registry &r, entity_t const &e) { r.get_components<Component>().erase(e._idx); } );

            // ~ return the sparse_array<Component> that we just added to our registry.
            return std::any_cast<sparse_array<Component> &>(_components_arrays[std::type_index(typeid(Component))]);
        };
        
        // ~ return the sparse_array<Component> that we just added to our registry.
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

// ~ Step 2.3: MANAGING ENTITIES
    // ~ 
        //<> class manager {

        /**
         * @brief spawn_entity
         * 
         * @return entity_t 
         */
        // ~ return entity_array.size + 1
        entity_t spawn_entity() // ~ create an entity
        {
            if (_killed_entities.size() != 0) {
                entity_t tmp = _killed_entities.back();
                _killed_entities.pop_back();
                return tmp;
            } else {
                    ++_entitys_count;
                    return entity_t(_entitys_count - 1);
            }
        };

        /**
         * @brief 
         * 
         * @param idx 
         * @return entity_t 
         */
        // ~ 
        entity_t entity_from_index(std::size_t idx) // ~ create an entity
        {
            return entity_t(idx);
        };

        /**
         * @brief 
         * 
         * @param e 
         * 
         */
        void kill_entity(entity_t const &e)
        {
            // * edit register_component();
            _killed_entities.push_back(e);
            for (auto f: _components_removes)
                f(*this, e);
        };

        /**
         * @brief 
         * 
         * @tparam Component 
         * @param to 
         * @param c 
         * @return sparse_array<Component>::reference_type 
         */
        template <typename Component>
        typename sparse_array<Component>::reference_type add_component(entity_t const &to, Component &&c)
        {
            get_components<Component>().emplace_at(to._idx, c);
            return get_components<Component>()[to._idx];
        };

        /**
         * @brief
         *
         * @tparam Component
         * @tparam Params
         * @param to
         * @param p
         * @return sparse_array <Component>::reference_type
         */
        template <typename Component, typename ... Params>
        typename sparse_array <Component>::reference_type emplace_component(entity_t const &to, Params &&... p)
        {
            get_components<Component>().emplace_at(to._idx, p...);
            return get_components<Component>()[to._idx];
        };

        /**
         * @brief 
         * 
         * @tparam Component 
         * @param from 
         */
        template <typename Component>
        void remove_component(entity_t const &from)
        {
            get_components<Component>().erase(from._idx);
        };
        // <> };

    private :
        size_t _entitys_count = 0;
        std::vector<entity_t> _killed_entities;
        std::unordered_map<std::type_index, std::any> _components_arrays;
        std::vector<std::function<void(registry &, entity_t const &)>> _components_removes;
};

// # TEST ENTITIES 2.3
int main(int argc, char const *argv[])
{
    registry reg;
    // ! spawn & entity from index
    std::cout << "2.2 - Register_component" << std::endl;
    reg.register_component<float>();
    reg.register_component<int>();
    reg.get_components<int>().display();
    reg.get_components<float>().display();
    std::cout << std::endl << "2.3 - Spawn_entity" << std::endl;
    std::cout << reg.spawn_entity()._idx << std::endl;
    std::cout << reg.spawn_entity()._idx << std::endl;
    std::cout << reg.spawn_entity()._idx << std::endl;
    std::cout << reg.spawn_entity()._idx << std::endl;
    std::cout << reg.spawn_entity()._idx << std::endl;
    entity_t e = reg.spawn_entity();
    std::cout << e._idx << std::endl;
    reg.get_components<float>().display();
    reg.get_components<int>().display();
    std::cout << std::endl << "2.3.5 - Add_component" << std::endl;
    reg.add_component<float>(e, 3);
    reg.add_component<int>(e, 3);
    reg.get_components<float>().display();
    reg.get_components<int>().display();
    std::cout << std::endl << "2.3.5 - Entity_from_index" << std::endl;
    reg.add_component<float>(reg.entity_from_index(0), 1);
    reg.add_component<int>(reg.entity_from_index(0), 3);
    reg.get_components<float>().display();
    reg.get_components<int>().display();
    std::cout << std::endl << "2.3 - Kill_entity" << std::endl;    
    reg.kill_entity(reg.entity_from_index(0));
    reg.kill_entity(reg.entity_from_index(4));
    reg.kill_entity(reg.entity_from_index(2));
    reg.get_components<float>().display();
    reg.get_components<int>().display();
    std::cout << std::endl << "2.3 - Spawn_entity" << std::endl;
    std::cout << reg.spawn_entity()._idx << std::endl;
    std::cout << reg.spawn_entity()._idx << std::endl;
    std::cout << reg.spawn_entity()._idx << std::endl;
    std::cout << reg.spawn_entity()._idx << std::endl;
    std::cout << std::endl << "2.3.5 - Emplace_component" << std::endl;
    reg.emplace_component<float>(e, -1.f, -2.f); // ?? pourquoi l'emplace ecris sur un autre entity_t ?
    reg.get_components<float>().display();
    reg.get_components<int>().display();
    std::cout << std::endl << "2.3.5 - Remove_component" << std::endl;
    reg.remove_component<float>(e);
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
