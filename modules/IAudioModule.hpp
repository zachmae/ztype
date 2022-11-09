/*
** EPITECH PROJECT, 2022
** archi
** File description:
** IAudioModule
*/

#ifndef IAUDIOMODULE_HPP_
#define IAUDIOMODULE_HPP_

#include <string>

/*!
 *  \addtogroup Modules
 *  @{
 */

namespace modules {

    /**
     * @brief Enumerate the different status of a sound
     *
     */
    enum MusicStatus {
        PLAYING,
        PAUSED,
        STOPPED
    };

    /**
     * @brief Interface for the audio module
     *
     */
    class IAudioModule
    {
        public:

            virtual ~IAudioModule() = default;

            /**
             * @brief load and set an audio file
             *
             * @param source_path : path to the asset file
             */
            virtual void setSource(std::string source_path) = 0;

            /**
             * @brief play the audio source
             *
             */
            virtual void play() = 0;

            /**
             * @brief pause the audio source
             *
             */
            virtual void pause() = 0;

            /**
             * @brief stop the audio source
             *
             */
            virtual void stop() = 0;

            /**
             * @brief Set the volume of the audio source
             *
             * @param volume : float that correspond to the volume on a scale of 0 to 100
             */
            virtual void setVolume(float volume) = 0;

            /**
             * @brief Get the status of the audio source
             *
             * @return MusicStatus : status that correspond of an enum given above
             */
            virtual MusicStatus getStatus() = 0;
    };

    /**
     * @brief Interface for the music module
     *
     */
    class IMusicModule
    {
        public:
            virtual ~IMusicModule() = default;

            /**
             * @brief load and set an audio file
             *
             * @param source_path : path to the asset file
             */
            virtual void setSource(std::string source_path) = 0;

            /**
             * @brief play the audio source
             *
             */
            virtual void play() = 0;

            /**
             * @brief pause the audio source
             *
             */
            virtual void pause() = 0;

            /**
             * @brief stop the audio source
             *
             */
            virtual void stop() = 0;

            /**
             * @brief Set the Volume of the audio source
             *
             * @param volume : a float going from 0 to 100
             */
            virtual void setVolume(float volume) = 0;

            /**
             * @brief Set the Loop of the audio source
             *
             * @param loop : loop if true
             */
            virtual void setLoop(bool loop) = 0;

            /**
             * @brief Get the Loop of the audio source
             *
             * @return true : is looping
             * @return false : don't loop
             */
            virtual bool getLoop() = 0;

            /**
             * @brief Get the status of the audio source
             *
             * @return MusicStatus : status that correspond of an enum given above
             */
            virtual MusicStatus getStatus() = 0;

    };
}

#endif /* !IAUDIOMODULE_HPP_ */