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

namespace modules {
    class SFMLAudioModule : public IAudioModule {
        public:
            SFMLAudioModule() = default;
            SFMLAudioModule(const std::string path) {
                setSource(path);
            }
            ~SFMLAudioModule() = default;

            void setSource(std::string source_path) override {
                _buffer.loadFromFile(source_path);
                _sound.setBuffer(_buffer);
            }

            void play() override {
                _sound.play();
            }

            void pause() override {
                _sound.pause();
            }

            void stop() override {
                _sound.stop();
            }

            void setVolume(float volume) override {
                _sound.setVolume(volume);
            }

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
            SFMLMusicModule(const std::string path) {
                setSource(path);
            }
            SFMLMusicModule() = default;
            ~SFMLMusicModule() = default;

            void setSource(std::string source_path) override {
                _music.openFromFile(source_path);
            }

            void play() override {
                _music.play();
            }

            void pause() override {
                _music.pause();
            }

            void stop() override {
                _music.stop();
            }

            void setVolume(float volume) override {
                _music.setVolume(volume);
            }

            void setLoop(bool loop) override {
                _music.setLoop(loop);
            }

            bool getLoop() override {
                return _music.getLoop();
            }

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
