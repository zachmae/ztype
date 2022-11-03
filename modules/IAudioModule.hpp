/*
** EPITECH PROJECT, 2022
** archi
** File description:
** IAudioModule
*/

#ifndef IAUDIOMODULE_HPP_
#define IAUDIOMODULE_HPP_

#include <string>

namespace modules {
    enum MusicStatus {
        PLAYING,
        PAUSED,
        STOPPED
    };

    class IAudioModule
    {
        public:

            virtual ~IAudioModule() = default;
            // ALL FILE TYPES MUST BE AT THE PATH SPECIFIED
            // MUST: loads and set an audio file
            //ex SFML:
            // assetPath = ./Assets/Pacman/enemy/sound
            // real path = ./Assets/Pacman/enmey/font.ttf

            virtual void setSource(std::string source_path) = 0;

            // MUST play the audio source (maybe instantiate it here)
            virtual void play() = 0;

            // MUST pause the audio source
            virtual void pause() = 0;

            // MUST Stop the audio source (maybe destroy the instance here)
            virtual void stop() = 0;

            // Must set the volume
            virtual void setVolume(float volume) = 0;

            // Must get the status of the audio source
            virtual MusicStatus getStatus() = 0;
    };

    class IMusicModule
    {
        public:
            virtual ~IMusicModule() = default;
            // ALL FILE TYPES MUST BE AT THE PATH SPECIFIED
            // MUST: loads and set an audio file
            //ex SFML:
            // assetPath = ./Assets/Pacman/enemy/sound
            // real path = ./Assets/Pacman/enmey/font.ttf

            virtual void setSource(std::string source_path) = 0;

            // MUST play the audio source (maybe instantiate it here)
            virtual void play() = 0;

            // MUST pause the audio source
            virtual void pause() = 0;

            // MUST Stop the audio source (maybe destroy the instance here)
            virtual void stop() = 0;

            // Must set the volume
            virtual void setVolume(float volume) = 0;

            // Must set the loop
            virtual void setLoop(bool loop) = 0;

            // Must get the status of the loop
            virtual bool getLoop() = 0;

            // Must get the status of the music
            virtual MusicStatus getStatus() = 0;

    };
}

#endif /* !IAUDIOMODULE_HPP_ */