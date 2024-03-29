/*
** EPITECH PROJECT, 2022
** B-CPP-500-PAR-5-1-rtype-zacharie.lawson
** File description:
** SpriteManager
*/

#include "SFMLAudioModule.hpp"
#include <map>

#ifndef AUDIOMANAGER_HPP_
#define AUDIOMANAGER_HPP_

/*!
 *  \addtogroup StorageManager
 *  @{
 */

template <typename Key>
class AudioManager;

template<typename Key>
using AudioManager_ref = AudioManager<Key> &;


/**
 * @brief AudioManager
 *
 * @tparam T
 * @tparam Value
 */
template<typename Key/*, typename Value*/>
class AudioManager {
    public:
        using AStorage = std::map<Key, modules::SFMLAudioModule>;

        /**
         * @brief Add
         *
         * @param k : Key
         * @param v : Value
         */
        void Add(Key k, modules::SFMLAudioModule &v)
        {
            _storage.insert(std::pair<Key, modules::SFMLAudioModule>(k, v));
        };

        /**
         * @brief Add
         *
         * @param k : Key
         * @param path : Path
         */
        void Add(Key k, std::string path)
        {
            _storage[k].setSource(path);
        };

        /**
         * @brief Get
         *
         * @param k : key
         * @return modules::SFMLAudioModule&
         */
        modules::SFMLAudioModule &Get(Key k)
        {
            return _storage[k];
        };

        /**
         * @brief play the sound at the given key
         *
         * @param k : key
         */
        void play(Key k)
        {
            _storage[k].play();
        };

        /**
         * @brief stop the sound at the given key
         *
         * @param k : key
         */
        void stop(Key k)
        {
            _storage[k].stop();
        };

        /**
         * @brief pause the sound at the given key
         *
         * @param k : key
         */
        void pause(Key k)
        {
            _storage[k].pause();
        };

        /**
         * @brief Stop every sound
         *
         */
        void stopAll()
        {
            for (auto &it : _storage)
                it.second.stop();
        };

        /**
         * @brief set volume
         *
         * @param volume : volume to be set
         */
        void setVolume(float volume) {
            _volume = volume;
            updateVolume();
        };

        /**
         * @brief get volume
         *
         */
        float getVolume() {
            return _volume;
        }

        /**
         * @brief update the volume of the sound
         *
         */
        void updateVolume() {
            for (auto &it : _storage)
                it.second.setVolume(_volume);
        }

        /**
         * @brief Get the Status object
         *
         * @param key : the key of the sound
         * @return sf::Sound::Status
         */
        modules::MusicStatus getStatus(Key k)
        {
            return _storage[k].getStatus();
        };

    private:
        float _volume = 50;
        AStorage _storage;
};


#endif /* !SPRITEMANAGER_HPP_ */
