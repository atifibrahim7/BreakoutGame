#include <sdk/input.h>
#include <sdk/window.h>
#include <vector>
#include "Paddle.h";

int main() {
    SDK::Window window(WINDOW_WIDTH, WINDOW_HEIGHT, "Breakout");

    Paddle paddle(window);
    Ball*  ball = new Ball(window);
    BrickManager brickManager(window);

    double lastTime = window.getSecondsSinceCreation();

    while (window.isOpen()) {
        double currentTime = window.getSecondsSinceCreation();
        double deltaTime = currentTime - lastTime;
        lastTime = currentTime;

        paddle.update(deltaTime);
        ball->updateWithPaddle(paddle.getX(), paddle.getWidth());
        ball->update(deltaTime);

        paddle.checkBallCollision(*ball);
        brickManager.checkCollisions(*ball);

        if (ball->isOffScreen()) {
            delete ball;
			ball = new Ball(window);
        }

        if (brickManager.allBricksDestroyed()) {
            // Handle win condition (could add game over text here)
            break;
        }

        window.draw();
    }

    return 0;
}