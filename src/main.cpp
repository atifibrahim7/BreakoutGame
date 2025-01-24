#include <sdk/input.h>
#include <sdk/window.h>
#include <vector>
#include "Paddle.h";



int main() {
    SDK::Window window(WINDOW_WIDTH, WINDOW_HEIGHT, "Breakout");

    Paddle paddle(window);

    double lastTime = window.getSecondsSinceCreation();

    while (window.isOpen()) {
        double currentTime = window.getSecondsSinceCreation();
        double deltaTime = currentTime - lastTime;
        lastTime = currentTime;

        paddle.update(deltaTime);

        window.draw();
    }

    return 0;
}