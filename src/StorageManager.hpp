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
 *
 * @author perry.chouteau@epitech.eu
 */
//template<typename _Res, typename... _ArgTypes>
//class function<_Res(_ArgTypes...)>
template<typename Key, typename Value, typename... _ArgTypes>
class StorageManager {
    public:
        using TStorage = std::map<Key, Value>;

        StorageManager(std::function<Value(_ArgTypes...)> f)
        : _f(f) {}

        /**
         * @brief Add
         *
         * @param k
         * @param v
         */
        void Add(Key k, Value &v)
        {
            _storage.insert(std::pair<Key, Value>(k, v));
        }

        /**
         * @brief Add
         *
         * @param k
         * @param path
         * @param f
         *
         */
        void Add(Key k, _ArgTypes... vc)
        {
            _storage.insert(std::pair<Key, Value>(k, _f(vc)));
        }

        /**
         * @brief Get
         *
         * @param t
         * @return sf::Sprite
         */
        Value &Get(Key k)
        {
              return _storage[k];
        }

    private:
        TStorage _storage;
        std::function<Value(_ArgTypes...)> _f;
};

//#endif /* !SPRITEMANAGER_HPP_ */
