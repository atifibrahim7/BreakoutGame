#pragma once 
#include <vector>
#include "Ball.h"
#pragma region Paddle 
class Paddle {
private:
    SDK::Window& window;
    SDK::SpriteID leftPart;
    SDK::SpriteID middlePart;
    SDK::SpriteID rightPart;
    float xPosition;  // Current x position of paddle's left edge
    float totalPaddleWidth; 

public:
    Paddle(SDK::Window& gameWindow) : window(gameWindow) {
        totalPaddleWidth = 3 * (PADDLE_PART_WIDTH);

        xPosition = (WINDOW_WIDTH - totalPaddleWidth) / 2;

        leftPart = window.createSprite(SDK::SpriteType::PaddleLeft,
            xPosition, PADDLE_Y);
        middlePart = window.createSprite(SDK::SpriteType::PaddleMid,
            xPosition + (PADDLE_PART_WIDTH), PADDLE_Y);
        rightPart = window.createSprite(SDK::SpriteType::PaddleRight,
            xPosition + (2 * PADDLE_PART_WIDTH), PADDLE_Y);
    }

    void update(double deltaTime) {
        float oldX = xPosition;

        // Handle input
        if (SDK::isButtonPressed(SDK::Button::Left)) {
            xPosition -= PADDLE_SPEED * deltaTime;
        }
        if (SDK::isButtonPressed(SDK::Button::Right)) {
            xPosition += PADDLE_SPEED * deltaTime;
        }

        if (xPosition < 0) {
            xPosition = 0;
        }
        if (xPosition > WINDOW_WIDTH - totalPaddleWidth) {
            xPosition = WINDOW_WIDTH - totalPaddleWidth;
        }

        if (oldX != xPosition) {
            window.moveSprite(leftPart, xPosition, PADDLE_Y);
            window.moveSprite(middlePart, xPosition + (PADDLE_PART_WIDTH ), PADDLE_Y);
            window.moveSprite(rightPart, xPosition + (2 * PADDLE_PART_WIDTH ), PADDLE_Y);
        }
    }
    float getWidth() const { return 3 * PADDLE_PART_WIDTH; }
    float getX() const { return xPosition; }

    bool checkBallCollision(Ball& ball) {
        float ballX = ball.getX();
        float ballY = ball.getY();

        if (ballY + 2 * BALL_RADIUS >= PADDLE_Y && ballY <= PADDLE_Y + PADDLE_PART_WIDTH) {
            if (ballX + 2 * BALL_RADIUS >= xPosition && ballX <= xPosition + getWidth()) {
                float hitPos = (ballX + BALL_RADIUS - (xPosition + getWidth() / 2)) / (getWidth() / 2);
                ball.bounceOffPaddle(hitPos);
                return true;
            }
        }
        return false;
    }
    ~Paddle() {
        window.removeSprite(leftPart);
        window.removeSprite(middlePart);
        window.removeSprite(rightPart);
    }
};
#pragma endregion