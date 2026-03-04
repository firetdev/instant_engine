#pragma once

#include "basecomponent.hpp"

#include <SFML/Audio.hpp>
#include <string>
#include <memory>

struct AudioPlayer : public BaseComponent {
private:
    sf::Sound sound;
    std::shared_ptr<sf::SoundBuffer> buffer;

public:
    float volume = 100.0f;  // Range: 0 - 100
    float pitch = 1.0f;  // Also affects speed
    bool looping = false;

    AudioPlayer(const std::string& filepath) {
        if (!load(filepath))
            std::cout << "AudioPlayer failed to initialize" << std::endl;
    }

    bool load(const std::string& filepath) {
        buffer = std::make_shared<sf::SoundBuffer>();

        if (!buffer->loadFromFile(filepath))
            return false;

        sound.setBuffer(*buffer);
        applyProperties();
        return true;
    }

    void applyProperties() {
        sound.setVolume(volume);
        sound.setPitch(pitch);
        sound.setLooping(looping);
    }

    void play() {
        applyProperties();
        sound.play();
    }

    void stop() {
        sound.stop();
    }

    bool isPlaying() const {
        return sound.getStatus() == sf::Sound::Status::Playing;
    }
};
