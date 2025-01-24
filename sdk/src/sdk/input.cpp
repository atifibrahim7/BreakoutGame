#include <sdk/input.h>

#include <SFML/Window/Keyboard.hpp>

namespace SDK {

bool isButtonPressed(Button button) {
    sf::Keyboard::Key keys[3] = {
        sf::Keyboard::A,
        sf::Keyboard::D,
        sf::Keyboard::Space
    };

    return sf::Keyboard::isKeyPressed(keys[static_cast<int>(button)]);
}

} // SDK namespace
