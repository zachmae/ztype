/*
** EPITECH PROJECT, 2022
** B-CPP-500-PAR-5-1-rtype-zacharie.lawson
** File description:
** init
*/


#include "SceneManager/SceneManager.hpp"
#include "SpriteManager.hpp" // add init scene deprecated cause shouldn't be used

#include "ProjectManager/ProjectComponent.hpp"
#include "UserComponent.hpp"
#include "SceneManager/SceneComponent.hpp"
#include "SceneManager/SceneManager.hpp"

#include "UserSystem.hpp"
#include "User/Systems/System.hpp"
#include "User/Scenes/Game/Game.hpp" // WHAT THE FUCK

#include "Network/Client.hpp"

#include "AudioManager.hpp"
#include "SpriteManager.hpp"

#include "sfml_ref.hpp"

namespace User {

    template <typename Key>
    void createNewClient(Registry_ref reg, SceneManager_ref<Key> scenes, SpriteManager_ref<Key> _sm, Client &client);

} // namespace User