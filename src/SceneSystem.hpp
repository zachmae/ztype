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

#include "Component.hpp"
#include "SceneComponent.hpp"


#ifndef SCENESYSTEM_HPP_
    #define SCENESYSTEM_HPP_

namespace SceneStd {

    template<typename Key>
    using SceneManager_ref = SceneManager<Key> &;

    void display_system(Registry_ref _ecs, SceneManager_ref<std::string> sm, Window_ref window)
    {
        std::vector<int> vi = sm.GetOrderedZtypePositiveOnly();
        auto &drawables = _ecs.get_components<drawable>();
        auto &positions = _ecs.get_components<position>();
        auto &SceneIds = _ecs.get_components<SceneId>();

        sm.GetScenes();
        for (const auto& zIndex: vi) { //burk but it works
            for (size_t i = 0; i < drawables.size() && i < positions.size() && i < SceneIds.size(); ++i) { //can we get an other item
                if (drawables[i] && positions[i] && SceneIds[i]) { //can we draw it
                    for (auto &scene: sm.GetScenes()) { //loop on the scene
                        if (SceneIds[i]->_sceneId == scene.second.GetId() && zIndex == scene.second.GetZIndex()) { //isItInAScene & isItTheRightZIndex
                            drawables[i]->sprite.setPosition({positions[i]->x, positions[i]->y}); //set the position
                            window.draw(drawables[i]->sprite);  //draw it
                            break;  //break the loop
                        }
                    }
                }
            }
        }
    }

};

#endif /* !SCENESYSTEM_HPP_ */