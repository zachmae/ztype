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
 *  \addtogroup GameStd
 *  @{
 */

//! Namespace for all game related content like the components
namespace GameStd {


    /**
     * @brief MusicManager
     *
     * @tparam T
     * @tparam Value
     */
    template<typename Key/*, typename Value*/>
    class MusicManager {
        public:
            using AStorage = std::map<Key, modules::SFMLMusicModule>;

            /**
             * @brief Add
             *
             * @param t
             * @param v
             */
            void Add(Key k, modules::SFMLMusicModule &v)
            {
                _storage.insert(std::pair<Key, modules::SFMLAudioModule>(k, v));
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
                _storage[k].setSource(path);
            };

            /**
             * @brief Get
             *
             * @param t
             * @return sf::Sound&
             */
            sf::Sound &Get(Key k)
            {
                return _storage[k];
            };

            /**
             * @brief play the sound at the given key
             *
             * @param key
             */
            void play(Key k)
            {
                _storage[k].play();
                setLoop(k);
            };

            /**
             * @brief stop the sound at the given key
             *
             * @param key
             */
            void stop(Key k)
            {
                _storage[k].stop();
            };

            /**
             * @brief pause the sound at the given key
             *
             * @param key
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
             * @param key
             * @param path
             */
            void setLoop(Key k)
            {
                _storage[k].setLoop(true);
            };

            /**
             * @brief Stop the audio loop at the given key
             *
             * @param key
             */
            void stopLoop(Key k)
            {
                _storage[k].setLoop(false);
            };

            /**
             * @brief set volume
             *
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
             * @param key
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
             * @param key
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

};


#endif /* !SPRITEMANAGER_HPP_ */
