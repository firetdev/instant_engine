// Input namespace

#pragma once

#include <SFML/Graphics.hpp>

#include <map>
#include <string>

namespace Input {
inline std::map<std::string, bool> inputs;

inline void update() {
    inputs["Escape"] = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape);
    inputs["Escape"] = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape);
    inputs["LControl"] = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LControl);
    inputs["LShift"] = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift);
    inputs["LAlt"] = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LAlt);
    inputs["LSystem"] = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LSystem);
    inputs["RControl"] = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::RControl);
    inputs["RShift"] = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::RShift);
    inputs["RAlt"] = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::RAlt);
    inputs["RSystem"] = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::RSystem);
    inputs["Menu"] = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Menu);
    inputs["LBracket"] = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LBracket);
    inputs["RBracket"] = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::RBracket);
    inputs[";"] = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Semicolon);
    inputs[","] = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Comma);
    inputs["."] = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Period);
    inputs["/"] = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Slash);
    inputs["\\"] = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Backslash);
    inputs["="] = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Equal);
    inputs["-"] = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Subtract);
    inputs["Space"] = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space);
    inputs["Enter"] = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter);
    inputs["Back"] = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Backspace);
    inputs["Tab"] = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Tab);
    inputs["Page Up"] = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::PageUp);
    inputs["Page Down"] = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::PageDown);
    inputs["End"] = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::End);
    inputs["Home"] = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Home);
    inputs["Insert"] = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Insert);
    inputs["Delete"] = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Delete);
    inputs["+"] = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Add);
    inputs["Left"] = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left);
    inputs["Right"] = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right);
    inputs["Up"] = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up);
    inputs["Down"] = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down);
    inputs["0"] = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Numpad0);
    inputs["1"] = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Numpad1);
    inputs["2"] = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Numpad2);
    inputs["3"] = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Numpad3);
    inputs["4"] = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Numpad4);
    inputs["5"] = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Numpad5);
    inputs["6"] = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Numpad6);
    inputs["7"] = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Numpad7);
    inputs["8"] = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Numpad8);
    inputs["9"] = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Numpad9);
    inputs["F1"] = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::F1);
    inputs["F2"] = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::F2);
    inputs["F3"] = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::F3);
    inputs["F4"] = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::F4);
    inputs["F5"] = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::F5);
    inputs["F6"] = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::F6);
    inputs["F7"] = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::F7);
    inputs["F8"] = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::F8);
    inputs["F9"] = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::F9);
    inputs["F10"] = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::F10);
    inputs["F11"] = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::F11);
    inputs["F12"] = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::F12);
    inputs["F13"] = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::F13);
    inputs["F14"] = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::F14);
    inputs["F15"] = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::F15);
    inputs["Pause"] = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Pause);
    inputs["a"] = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A);
    inputs["b"] = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::B);
    inputs["c"] = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::C);
    inputs["d"] = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D);
    inputs["e"] = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::E);
    inputs["f"] = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::F);
    inputs["g"] = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::G);
    inputs["h"] = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::H);
    inputs["i"] = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::I);
    inputs["j"] = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::J);
    inputs["k"] = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::K);
    inputs["l"] = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::L);
    inputs["m"] = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::M);
    inputs["n"] = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::N);
    inputs["o"] = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::O);
    inputs["p"] = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::P);
    inputs["q"] = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q);
    inputs["r"] = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::R);
    inputs["s"] = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S);
    inputs["t"] = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::T);
    inputs["u"] = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::U);
    inputs["v"] = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::V);
    inputs["w"] = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W);
    inputs["x"] = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::X);
    inputs["y"] = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Y);
    inputs["z"] = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Z);
    inputs["leftclick"] = sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);
    inputs["rightclick"] = sf::Mouse::isButtonPressed(sf::Mouse::Button::Right);
    inputs["middleclick"] = sf::Mouse::isButtonPressed(sf::Mouse::Button::Middle);
}
}
