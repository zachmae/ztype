/*
** EPITECH PROJECT, 2022
** B-CPP-500-PAR-5-1-rtype-zacharie.lawson
** File description:
** SpriteManager
*/

#include "SFMLAudioModule.hpp"
#include <map>

#ifndef MUSICMANAGER_HPP_
#define MUSICMANAGER_HPP_

/*!
 *  \addtogroup StorageManager
 *  @{
 */

template <typename Key>
class MusicManager;

template<typename Key>
using MusicManager_ref = MusicManager<Key> &;


/**
 * @brief MusicManager
 *
 * @tparam T
 * @tparam Value
 */
template<typename Key>
class MusicManager {
    public:

        using AStorage = std::map<Key, modules::SFMLMusicModule>;

        /**
         * @brief Add
         *
         * @param k : Key
         * @param v : Value
         */
        void Add(Key k, modules::SFMLMusicModule &v)
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
         * @param k : Key
         * @return modules::SFMLMusicModule&
         */
        modules::SFMLMusicModule &Get(Key k)
        {
            return _storage[k];
        };

        /**
         * @brief play the sound at the given key
         *
         * @param k : Key
         */
        void play(Key k)
        {
            _storage[k].play();
            setLoop(k);
        };

        /**
         * @brief stop the sound at the given key
         *
         * @param k : Key
         */
        void stop(Key k)
        {
            _storage[k].stop();
        };

        /**
         * @brief pause the sound at the given key
         *
         * @param k : Key
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
         * @brief Loop the sound at the given buffer
         *
         * @param k : Key
         */
        void setLoop(Key k)
        {
            _storage[k].setLoop(true);
        };

        /**
         * @brief Stop the audio loop at the given key
         *
         * @param k : Key
         */
        void stopLoop(Key k)
        {
            _storage[k].setLoop(false);
        };

        /**
         * @brief set volume
         *
         * @param volume :volume to be set
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
         * @brief get loop of the sound at the given key
         *
         * @param k : Key
         *
         * @return bool
         */
        bool getLoop(Key k)
        {
            return _storage[k].getLoop();
        };

        /**
         * @brief Get the Status object
         *
         * @param k : Key
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
