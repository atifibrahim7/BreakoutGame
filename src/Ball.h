#pragma once
#include "Paddle.h"
#include <SDK/Window.h>  // Adjust if needed for your SDK include
#include "Constants.h"
#pragma region Ball

class Ball {
private:
    SDK::Window& window;
    SDK::SpriteID ballSprite;
    float xPosition;
    float yPosition;
    float xVelocity;
    float yVelocity;
    bool isLaunched;

public:
    Ball(SDK::Window& gameWindow) :
        window(gameWindow),
        isLaunched(false),
        xVelocity(BALL_SPEED* cos(INITIAL_ANGLE)),
        yVelocity(BALL_SPEED* sin(INITIAL_ANGLE)) {

        ballSprite = window.createSprite(SDK::SpriteType::Ball, 0, 0);
    }

    void updateWithPaddle(float paddleX, float paddleWidth) {
        if (!isLaunched) {
            xPosition = paddleX + (paddleWidth / 2) - BALL_RADIUS;
            yPosition = PADDLE_Y - 2 * BALL_RADIUS;  // Just above paddle
            window.moveSprite(ballSprite, xPosition, yPosition);

            if (SDK::isButtonPressed(SDK::Button::Fire)) {
                isLaunched = true;
            }
        }
    }
	// Source : StackOverflow
    void update(double deltaTime) {
        if (!isLaunched) {
            return;
        }

        xPosition += xVelocity * deltaTime;
        yPosition += yVelocity * deltaTime;

        if (xPosition <= 0) {
            xPosition = 0;
            xVelocity = -xVelocity;
        }
        if (xPosition >= WINDOW_WIDTH - 2 * BALL_RADIUS) {
            xPosition = WINDOW_WIDTH - 2 * BALL_RADIUS;
            xVelocity = -xVelocity;
        }
        if (yPosition <= 0) {
            yPosition = 0;
            yVelocity = -yVelocity;
        }

        window.moveSprite(ballSprite, xPosition, yPosition);
    }
    void reverseX() { xVelocity = -xVelocity; }
    void reverseY() { yVelocity = -yVelocity; }
    bool isOffScreen() const {
        return yPosition > WINDOW_HEIGHT;
    }

    float getX() const { return xPosition; }
    float getY() const { return yPosition; }

    void bounceOffPaddle(float hitPosition) {
        float angle = hitPosition * (PI / 3);  

        yVelocity = -BALL_SPEED * sin(PI / 2 - angle);
        xVelocity = BALL_SPEED * cos(PI / 2 - angle);
    }

    ~Ball() {
        window.removeSprite(ballSprite);
    }
};
#pragma endregion