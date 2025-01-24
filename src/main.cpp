#include <sdk/input.h>
#include <sdk/window.h>
#include <vector>
#include "Paddle.h";

int main() {
    SDK::Window window(WINDOW_WIDTH, WINDOW_HEIGHT, "Breakout");
    SDK::TextID gameOverText; 
    Paddle *paddle = new Paddle(window);
    Ball*  ball = new Ball(window);
    BrickManager*  brickManager = new BrickManager(window);
    SDK::TextID winText; 
    double lastTime = window.getSecondsSinceCreation();
    bool gameOver = false;
    while (window.isOpen()) {
        double currentTime = window.getSecondsSinceCreation();
        double deltaTime = currentTime - lastTime;
        lastTime = currentTime;

        if (!gameOver) {
            paddle->update(deltaTime);
            ball->updateWithPaddle(paddle->getX(), paddle->getWidth());
            ball->update(deltaTime);

            paddle->checkBallCollision(*ball);
            brickManager->checkCollisions(*ball);

            if (ball->isOffScreen()) {
                if (!brickManager->loseLife()) {
                    gameOver = true;
                   gameOverText = window.createText("Game Over!", 40,
                        WINDOW_WIDTH / 2 - 100, WINDOW_HEIGHT / 2 - 20);
                }
                else {
                    ball = new Ball(window);
                }
            }

            if (brickManager->allBricksDestroyed()) {
               winText = window.createText("You Win!", 40,
                    WINDOW_WIDTH / 2 - 80, WINDOW_HEIGHT / 2 - 20);
                gameOver = true;
            }
        }
        else {
            if (SDK::isButtonPressed(SDK::Button::Fire)) {
                gameOver = false;
				window.removeText(winText);
                delete brickManager;
				delete ball;
				delete paddle;
				window.removeText(gameOverText);

                brickManager = new BrickManager(window);
                ball = new  Ball(window);
                paddle = new Paddle(window);
            }
        }

        window.draw();
    }

    return 0;
}