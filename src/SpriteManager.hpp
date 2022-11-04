/*
** EPITECH PROJECT, 2022
** B-CPP-500-PAR-5-1-rtype-zacharie.lawson
** File description:
** SpriteManager
*/

#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include <map>

#ifndef SPRITEMANAGER_HPP_
    #define SPRITEMANAGER_HPP_

/*!
 *  \addtogroup StorageManager
 *  @{
 */

template <typename Key>
class SpriteManager;

template<typename Key/*, typename Value*/>
using SpriteManager_ref = SpriteManager<Key> &;

/**
 * @brief Image structure that can associate a Texture and a Sprite
 *
 */
struct Image {
    sf::Texture texture;
    sf::Sprite sprite;
};

/**
 * @brief SpriteManager
 *
 * @tparam T
 * @tparam Value
 */
template<typename Key/*, typename Value*/>
class SpriteManager {
    public:
        using TStorage = std::map<Key, Image>;

    /**
     * @brief Add
     *
     * @param t
     * @param v
     */
    void Add(Key k, Image &v)
    {
        _storage.insert(std::pair<Key, Image>(k, v));
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
        _storage[k].texture.loadFromFile(path);
        _storage[k].sprite.setTexture(_storage[k].texture);
    };

        /**
         * @brief Get
         *
         * @param t
         * @return sf::Sprite
         */
        sf::Sprite &Get(Key k)
        {
            return _storage[k].sprite;
        };

    private:
        TStorage _storage;
};

#endif /* !SPRITEMANAGER_HPP_ */
