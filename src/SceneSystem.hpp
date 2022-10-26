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
#include "SceneManager.hpp"

#include <map>
#include <unordered_set>

#ifndef SCENESYSTEM_HPP_
    #define SCENESYSTEM_HPP_

namespace Scene {

    template<typename Key>
    using SceneManager_ref = SceneManager<Key> &;

    void display_system(Registry_ref _ecs, SceneManager_ref<std::string> sm, Window_ref window)
    {
        std::vector<int> vi;
        for (auto &scene: sm.GetScenes())
            if (!(scene.second.GetZIndex() < 0))
                vi.push_back(scene.second.GetId());
        std::sort(vi.begin(), vi.end());
        std::unordered_set<int> s;
        for (int i: vi)
            s.insert(i);
        vi.assign(s.begin(), s.end());
        sort(vi.begin(), vi.end());

        for (const auto& i: vi)
            for (auto &scene: sm.GetScenes()) {
            }
    }

    static void function() {

    };

};

#endif /* !SCENESYSTEM_HPP_ */