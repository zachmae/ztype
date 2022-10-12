#ifndef SPARSE_ARRAY_HPP_
#define SPARSE_ARRAY_HPP_

    #include <cstddef>
    #include <vector>
    #include <algorithm>
    #include <iostream>
    #include <optional>

    template <typename Component> // You can also mirror the definition of std::vector ,that takes an additional allocator.
    class sparse_array {
        public:
            using value_type = std::optional<Component>; // optional component type
            using reference_type = value_type &;
            using const_reference_type = value_type const &;
            using container_t = std ::vector<value_type>; // optionally add your allocator
            using size_type = typename container_t::size_type;
            using iterator = typename container_t::iterator;
            using const_iterator = typename container_t::const_iterator;

        public:
            sparse_array();                         // You can add more constructors .
            sparse_array(sparse_array const &);     // copy constructor
            sparse_array(sparse_array &&) noexcept; // move constructor
            ~sparse_array();
            sparse_array &operator=(sparse_array const &source) { return source; };     // copy assignment operator
            sparse_array &operator=(sparse_array &&source) noexcept { return source; }; // move assignment operator
            reference_type operator[](size_t idx) { return _data[idx]; };
            const_reference_type operator[](size_t idx) const { return _data[idx]; };
            iterator begin() { return _data.begin(); } ;
            const_iterator begin() const { return _data.cbegin(); };
            const_iterator cbegin() const { return _data.cbegin(); };
            iterator end() { return _data.end(); };
            const_iterator end() const { return _data.cend(); };
            const_iterator cend() const { return _data.cend(); };
            size_type size() const { return _data.size(); };
            reference_type insert_at(size_type pos, Component const &comp) { return _data.insert(_data.begin() + pos, comp); };
            reference_type insert_at(size_type pos, Component &&comp) { return _data.insert(_data.begin() + pos, std::move(comp)); };
            template <class... Params>
            reference_type emplace_at(size_type pos, Params &&...) { return _data.emplace(_data.begin() + pos, std::forward<Params>(...)); }; // optional
            void erase(size_type pos) { _data.erase(_data.begin() + pos); };
            size_type get_index(value_type const &arg) const { return _data.index(arg); };

            private:
                container_t _data;
    };

#endif /* !SPARSE_ARRAY_HPP_ */