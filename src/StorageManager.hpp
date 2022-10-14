/*
** EPITECH PROJECT, 2022
** B-CPP-500-PAR-5-1-rtype-zacharie.lawson
** File description:
** SpriteManager
*/

#include <SFML/Window.hpp>
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "SFML/System.hpp"
#include "SFML/Network.hpp"
#include <map>
#include "Scene.hpp"

//#ifndef SPRITEMANAGER_HPP_
//#define SPRITEMANAGER_HPP_

/**
 * @brief StorageManager
 *
 * @tparam T
 * @tparam Value
 */
template<typename Key, typename Value>
class SceneManager {
    public:
        using TStorage = std::map<Key, Value>;

        SceneManager(std::function<Value(<std::string)> f)
        : _f(f)
        {
        }

        /**
         * @brief Add
         *
         * @param k
         * @param v
         */
        void Add(Key k, Value &v)
        {
            _storage.insert(std::pair<Key, Value>(k, v));
        };

        /**
         * @brief Add
         *
         * @param k
         * @param path
         * @param f
         *
         */
        void Add(Key k, std::string path)
        {
            _storage.insert(std::pair<Key, Value>(k, _f(path)));
        };

        /**
         * @brief Get
         *
         * @param t
         * @return sf::Sprite
         */
        sf::Sprite &Get(Key k)
        {
//              return _storage[k].;
            return std::nullopt;
        };

    private:
        TStorage _storage;
        std::function<Value(<std::string)> _f;
};

//#endif /* !SPRITEMANAGER_HPP_ */
