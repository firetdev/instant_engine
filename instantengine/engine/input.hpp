// Input namespace

#pragma once

#include <SFML/Graphics.hpp>

#include <map>
#include <string>

namespace Input {
inline std::map<std::string, bool> inputs;

// Convert key to string
inline std::string keyToName(sf::Keyboard::Key code) {
    switch (code) {
        case sf::Keyboard::Key::Escape:     return "Escape";
        case sf::Keyboard::Key::LControl:   return "LControl";
        case sf::Keyboard::Key::LShift:     return "LShift";
        case sf::Keyboard::Key::LAlt:       return "LAlt";
        case sf::Keyboard::Key::LSystem:    return "LSystem";
        case sf::Keyboard::Key::RControl:   return "RControl";
        case sf::Keyboard::Key::RShift:     return "RShift";
        case sf::Keyboard::Key::RAlt:       return "RAlt";
        case sf::Keyboard::Key::RSystem:    return "RSystem";
        case sf::Keyboard::Key::Menu:       return "Menu";
        case sf::Keyboard::Key::LBracket:   return "LBracket";
        case sf::Keyboard::Key::RBracket:   return "RBracket";
        case sf::Keyboard::Key::Semicolon:  return ";";
        case sf::Keyboard::Key::Comma:      return ",";
        case sf::Keyboard::Key::Period:     return ".";
        case sf::Keyboard::Key::Slash:      return "/";
        case sf::Keyboard::Key::Backslash:  return "\\";
        case sf::Keyboard::Key::Equal:      return "=";
        case sf::Keyboard::Key::Subtract:   return "-";
        case sf::Keyboard::Key::Space:      return "Space";
        case sf::Keyboard::Key::Enter:      return "Enter";
        case sf::Keyboard::Key::Backspace:  return "Back";
        case sf::Keyboard::Key::Tab:        return "Tab";
        case sf::Keyboard::Key::PageUp:     return "Page Up";
        case sf::Keyboard::Key::PageDown:   return "Page Down";
        case sf::Keyboard::Key::End:        return "End";
        case sf::Keyboard::Key::Home:       return "Home";
        case sf::Keyboard::Key::Insert:     return "Insert";
        case sf::Keyboard::Key::Delete:     return "Delete";
        case sf::Keyboard::Key::Add:        return "+";
        case sf::Keyboard::Key::Left:       return "Left";
        case sf::Keyboard::Key::Right:      return "Right";
        case sf::Keyboard::Key::Up:         return "Up";
        case sf::Keyboard::Key::Down:       return "Down";
        case sf::Keyboard::Key::Numpad0:    return "0";
        case sf::Keyboard::Key::Numpad1:    return "1";
        case sf::Keyboard::Key::Numpad2:    return "2";
        case sf::Keyboard::Key::Numpad3:    return "3";
        case sf::Keyboard::Key::Numpad4:    return "4";
        case sf::Keyboard::Key::Numpad5:    return "5";
        case sf::Keyboard::Key::Numpad6:    return "6";
        case sf::Keyboard::Key::Numpad7:    return "7";
        case sf::Keyboard::Key::Numpad8:    return "8";
        case sf::Keyboard::Key::Numpad9:    return "9";
        case sf::Keyboard::Key::F1:         return "F1";
        case sf::Keyboard::Key::F2:         return "F2";
        case sf::Keyboard::Key::F3:         return "F3";
        case sf::Keyboard::Key::F4:         return "F4";
        case sf::Keyboard::Key::F5:         return "F5";
        case sf::Keyboard::Key::F6:         return "F6";
        case sf::Keyboard::Key::F7:         return "F7";
        case sf::Keyboard::Key::F8:         return "F8";
        case sf::Keyboard::Key::F9:         return "F9";
        case sf::Keyboard::Key::F10:        return "F10";
        case sf::Keyboard::Key::F11:        return "F11";
        case sf::Keyboard::Key::F12:        return "F12";
        case sf::Keyboard::Key::F13:        return "F13";
        case sf::Keyboard::Key::F14:        return "F14";
        case sf::Keyboard::Key::F15:        return "F15";
        case sf::Keyboard::Key::Pause:      return "Pause";

        case sf::Keyboard::Key::A: return "a";
        case sf::Keyboard::Key::B: return "b";
        case sf::Keyboard::Key::C: return "c";
        case sf::Keyboard::Key::D: return "d";
        case sf::Keyboard::Key::E: return "e";
        case sf::Keyboard::Key::F: return "f";
        case sf::Keyboard::Key::G: return "g";
        case sf::Keyboard::Key::H: return "h";
        case sf::Keyboard::Key::I: return "i";
        case sf::Keyboard::Key::J: return "j";
        case sf::Keyboard::Key::K: return "k";
        case sf::Keyboard::Key::L: return "l";
        case sf::Keyboard::Key::M: return "m";
        case sf::Keyboard::Key::N: return "n";
        case sf::Keyboard::Key::O: return "o";
        case sf::Keyboard::Key::P: return "p";
        case sf::Keyboard::Key::Q: return "q";
        case sf::Keyboard::Key::R: return "r";
        case sf::Keyboard::Key::S: return "s";
        case sf::Keyboard::Key::T: return "t";
        case sf::Keyboard::Key::U: return "u";
        case sf::Keyboard::Key::V: return "v";
        case sf::Keyboard::Key::W: return "w";
        case sf::Keyboard::Key::X: return "x";
        case sf::Keyboard::Key::Y: return "y";
        case sf::Keyboard::Key::Z: return "z";

        default: return "";
    }
}

// Convert mouse button to string
inline std::string mouseToName(sf::Mouse::Button btn) {
    switch (btn) {
        case sf::Mouse::Button::Left:   return "leftclick";
        case sf::Mouse::Button::Right:  return "rightclick";
        case sf::Mouse::Button::Middle: return "middleclick";
        default:                        return "";
    }
}

// Check events
inline void update(sf::RenderWindow& window) {
    while (const std::optional<sf::Event> opt = window.pollEvent()) {
        const sf::Event& event = *opt;

        // Window event
        if (event.is<sf::Event::Closed>()) {
            window.close();
            continue;
        }

        // Keyboard event
        if (event.is<sf::Event::KeyPressed>()) {
            const auto& e = event.getIf<sf::Event::KeyPressed>();
            inputs[ keyToName(e->code) ] = true;
        } else if (event.is<sf::Event::KeyReleased>()) {
            const auto& e = event.getIf<sf::Event::KeyReleased>();
            inputs[ keyToName(e->code) ] = false;
        }

        // Mouse event
        if (event.is<sf::Event::MouseButtonPressed>()) {
            const auto& e = event.getIf<sf::Event::MouseButtonPressed>();
            inputs[ mouseToName(e->button) ] = true;
        } else if (event.is<sf::Event::MouseButtonReleased>()) {
            const auto& e = event.getIf<sf::Event::MouseButtonReleased>();
            inputs[ mouseToName(e->button) ] = false;
        }
    }
}
}
