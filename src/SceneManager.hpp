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

#ifndef SCENEMANAGER_HPP_
    #define SCENEMANAGER_HPP_

/**
 * @brief SpriteManager
 *
 * @tparam T
 * @tparam Value
 **/
template<typename Key>
class SceneManager {
    public:
        using TStorage = std::map<Key, Scene>;

        /**
         * @brief Add
         *
         * @param t
         * @param v
         */
        void Add(Key k, const Scene &v)
        {
            _storage.insert(std::pair<Key, Scene>(k, v));
        };

        /**
         * @brief Add
         *
         * @param t
         * @param texture
         * @param f
         */
        void Add(Key k, std::string path)
        {
            _storage[k] = Scene();
        };

        /**
         * @brief Get
         *
         * @param t
         * @return Scene
         */
        Scene &Get(Key k)
        {
            return _storage.at(k);
        };

         std::map<Key, Scene> GetScenes()
        {
            return _storage;
        }

    private:
        TStorage _storage;
};

#endif /* !SCENEMANAGER_HPP_ */