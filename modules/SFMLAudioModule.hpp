/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** SFMLAudioModule
*/

#ifndef SFMLAUDIOMODULE_HPP_
    #define SFMLAUDIOMODULE_HPP_
    #include "SFML/Audio.hpp"
    #include "IAudioModule.hpp"

/*!
 *  \addtogroup Modules
 *  @{
 */

namespace modules {
    class SFMLAudioModule : public IAudioModule {
        public:
            SFMLAudioModule() = default;

            /**
             * @brief Construct a new SFMLAudioModule object
             *
             * @param path : relative path to the asset of the sound effect
             */
            SFMLAudioModule(const std::string path) {
                setSource(path);
            }
            ~SFMLAudioModule() = default;

            /**
             * @brief Set the Source object from the path
             *
             * @param path : relative path to the asset of the sound effect
             */
            void setSource(std::string source_path) override {
                _buffer.loadFromFile(source_path);
                _sound.setBuffer(_buffer);
            }

            /**
             * @brief Play the sound effect
             *
             */
            void play() override {
                _sound.play();
            }

            /**
             * @brief Pause the sound effect
             *
             */
            void pause() override {
                _sound.pause();
            }

            /**
             * @brief Stop the sound effect
             *
             */
            void stop() override {
                _sound.stop();
            }

            /**
             * @brief Set the Volume of the sound effect
             *
             * @param volume : volume of the sound effect
             */
            void setVolume(float volume) override {
                _sound.setVolume(volume);
            }

            /**
             * @brief Get the Status object
             *
             * @return MusicStatus : the current status of the sound effect
             */
            MusicStatus getStatus() override {
                if (_sound.getStatus() == sf::Sound::Status::Playing)
                    return MusicStatus::PLAYING;
                if (_sound.getStatus() == sf::Sound::Status::Paused)
                    return MusicStatus::PAUSED;
                return MusicStatus::STOPPED;
            }

        protected:
        private:
            sf::SoundBuffer _buffer;
            sf::Sound _sound;
    };

    class SFMLMusicModule : public IMusicModule {
        public:
            SFMLMusicModule() = default;

            /**
             * @brief Construct a new SFMLMusicModule object
             *
             * @param path : relative path to the asset of the music
             */
            SFMLMusicModule(const std::string path) {
                setSource(path);
            }

            ~SFMLMusicModule() = default;

            /**
             * @brief Set the Source object from the path
             *
             * @param path : relative path to the asset of the music
             */
            void setSource(std::string source_path) override {
                _music.openFromFile(source_path);
            }

            /**
             * @brief Play the music
             *
             */
            void play() override {
                _music.play();
            }

            /**
             * @brief Pause the music
             *
             */
            void pause() override {
                _music.pause();
            }

            /**
             * @brief Stop the music
             *
             */
            void stop() override {
                _music.stop();
            }

            /**
             * @brief Set the Volume of the music
             *
             * @param volume : volume of the music
             */
            void setVolume(float volume) override {
                _music.setVolume(volume);
            }

            /**
             * @brief set the Loop the music
             *
             * @param loop : boolean to loop the music
             */
            void setLoop(bool loop) override {
                _music.setLoop(loop);
            }

            /**
             * @brief Get the Loop status of the music
             *
             * @return true : if the music is looping
             * @return false : if the music is not looping
             */
            bool getLoop() override {
                return _music.getLoop();
            }

            /**
             * @brief Get the Status object
             *
             * @return MusicStatus : the current status of the music
             */
            MusicStatus getStatus() override {
                if (_music.getStatus() == sf::Music::Status::Playing)
                    return MusicStatus::PLAYING;
                if (_music.getStatus() == sf::Music::Status::Paused)
                    return MusicStatus::PAUSED;
                return MusicStatus::STOPPED;
            }

        protected:
        private:
            sf::Music _music;
    };
} // namespace modules

#endif /* !SFMLAUDIOMODULE_HPP_ */
