/*
** EPITECH PROJECT, 2022
** B-CPP-500-PAR-5-1-rtype-zacharie.lawson
** File description:
** SpriteManager
*/

#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "SFML/System.hpp"
#include "SFML/Network.hpp"
#include <map>

#ifndef AUDIOMANAGER_HPP_
#define AUDIOMANAGER_HPP_

/*!
 *  \addtogroup GameStd
 *  @{
 */

//! Namespace for all game related content like the components
namespace GameStd {

    /**
     * @brief Audio structure that can associate a Buffer and a Sound
     *
     */
    struct Audio {
        sf::SoundBuffer _buffer;
        sf::Sound _sound;
    };

    /**
     * @brief AudioManager
     *
     * @tparam T
     * @tparam Value
     */
    template<typename Key/*, typename Value*/>
    class AudioManager {
        public:
            using AStorage = std::map<Key, Audio>;

            /**
             * @brief Add
             *
             * @param t
             * @param v
             */
            void Add(Key k, Audio &v)
            {
                _storage.insert(std::pair<Key, Audio>(k, v));
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
                _storage[k]._buffer.loadFromFile(path);
                _storage[k]._sound.setBuffer(_storage[k]._buffer);
            };

            /**
             * @brief Get
             *
             * @param t
             * @return sf::Sound&
             */
            sf::Sound &Get(Key k)
            {
                return _storage[k]._sound;
            };

            /**
             * @brief play the sound at the given key
             *
             * @param key
             */
            void play(Key k)
            {
                _storage[k]._sound.play();
            };

            /**
             * @brief stop the sound at the given key
             *
             * @param key
             */
            void stop(Key k)
            {
                _storage[k]._sound.stop();
            };

            /**
             * @brief pause the sound at the given key
             *
             * @param key
             */
            void pause(Key k)
            {
                _storage[k]._sound.pause();
            };

            /**
             * @brief Stop every sound
             *
             */
            void stopAll()
            {
                for (auto &it : _storage)
                    it.second._sound.stop();
            };

            /**
             * @brief Loop the sound at the given buffer
             *
             * @param key
             * @param path
             */
            void setLoop(Key k)
            {
                _storage[k]._sound.setLoop(true);
            };

            /**
             * @brief Stop the audio loop at the given key
             *
             * @param key
             */
            void stopLoop(Key k)
            {
                _storage[k]._sound.setLoop(false);
            };

            /**
             * @brief set volume
             *
             */
            void setVolume(float volume) {
                _volume = volume;
                for (auto &it : _storage)
                    it.second._sound.setVolume(_volume);
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
                    it.second._sound.setVolume(_volume);
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
                return _storage[k]._sound.getLoop();
            };

            /**
             * @brief Get the Status object
             *
             * @param key
             * @return sf::Sound::Status
             */
            sf::Sound::Status getStatus(Key k)
            {
                return _storage[k]._sound.getStatus();
            };

        private:
            float _volume = 50;
            AStorage _storage;
    };

};


#endif /* !SPRITEMANAGER_HPP_ */
