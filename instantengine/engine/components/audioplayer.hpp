#pragma once

#include "basecomponent.hpp"

#include <SFML/Audio.hpp>
#include <string>
#include <memory>

struct AudioPlayer : public BaseComponent {
private:
    std::unique_ptr<sf::Sound> sound;
    std::shared_ptr<sf::SoundBuffer> buffer;

public:
    float volume = 100.0f;
    float pitch = 1.0f;
    bool looping = false;

    AudioPlayer(const std::string& filepath)
        : sound(nullptr), buffer(nullptr)
    {
        if (!load(filepath))
            std::cout << "AudioPlayer failed to initialize: " << filepath << std::endl;
    }

    bool load(const std::string& filepath) {
        buffer = std::make_shared<sf::SoundBuffer>();

        if (!buffer->loadFromFile(filepath))
            return false;

        sound = std::make_unique<sf::Sound>(*buffer);
        
        applyProperties();
        return true;
    }

    void applyProperties() {
        if (sound) {
            sound->setVolume(volume);
            sound->setPitch(pitch);
            sound->setLooping(looping);
        }
    }

    void play() {
        if (sound) {
            applyProperties();
            sound->play();
        }
    }

    void stop() {
        if (sound) sound->stop();
    }

    bool isPlaying() const {
        return (sound) ? (sound->getStatus() == sf::Sound::Status::Playing) : false;
    }
};
