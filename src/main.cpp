#include <sdk/input.h>
#include <sdk/window.h>
#include <vector>
#include "Paddle.h";



int main() {
    SDK::Window window(WINDOW_WIDTH, WINDOW_HEIGHT, "Breakout");

    Paddle paddle(window);
    Ball * ball = new Ball(window);

    double lastTime = window.getSecondsSinceCreation();

    while (window.isOpen()) {
        double currentTime = window.getSecondsSinceCreation();
        double deltaTime = currentTime - lastTime;
        lastTime = currentTime;

        paddle.update(deltaTime);
        ball->updateWithPaddle(paddle.getX(), paddle.getWidth());
        ball->update(deltaTime);

        paddle.checkBallCollision(*ball);

		// Check if ball is lost ---> TODO :  Life decrease  and if lifes == 0 then game over
        if (ball->isOffScreen()) {
            // Reset ball
			delete ball;
			ball = new Ball(window);
			
        }

        window.draw();
    }

    return 0;
}