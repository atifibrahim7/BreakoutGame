

#pragma once 


const float PADDLE_Y = 630.0f;         // Y position near bottom of screen
const float PADDLE_SPEED = 400.0f;     // Pixels per second
const float PADDLE_PART_WIDTH = 15.0f; // Width of each paddle sprite
const float WINDOW_WIDTH = 440.0f;
const float WINDOW_HEIGHT = 660.0f;

#pragma region Ball
const float BALL_SPEED = 300.0f;
const float BALL_RADIUS = 8.0f;  // Assuming ball sprite is 16x16 pixels
const float PI = 3.14159265359f;
const float INITIAL_ANGLE = -PI / 2; 

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