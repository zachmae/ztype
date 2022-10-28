/*
** EPITECH PROJECT, 2022
** B-CPP-500-PAR-5-1-rtype-zacharie.lawson
** File description:
** SpriteManager
*/

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <SFML/Network.hpp>

#include "Scene.hpp"

#include <map>
#include <unordered_set>

#ifndef SCENEMANAGER_HPP_
    #define SCENEMANAGER_HPP_

template<typename Key>
class SceneManager;

template<typename Key>
using SceneManager_ref = SceneManager<Key> &;

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

        std::vector<int> GetOrderedZtypePositiveOnly() {
            std::vector<int> vi;

            for (auto &scene: _storage)
                if (!(scene.second.GetZIndex() < 0))
                    vi.push_back(scene.second.GetZIndex());
            std::sort(vi.begin(), vi.end());
            std::unordered_set<int> s;
            for (int i: vi)
                s.insert(i);
            vi.assign(s.begin(), s.end());
            sort(vi.begin(), vi.end());

            return vi;
        };

        std::vector<int> GetDisplayOrderOfSceneID() {
            std::vector<int> vi = GetOrderedZtypePositiveOnly();
            std::vector<int> res;

            for (auto &zIndex: vi) {
                for (auto &scene: _storage) {
                    if (scene.second.GetZIndex() == zIndex)
                        res.push_back(scene.second.GetId());
                }
            }

            return res;
        };

    private:
        TStorage _storage;
};

#endif /* !SCENEMANAGER_HPP_ */