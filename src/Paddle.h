
const float PADDLE_Y = 630.0f;         // Y position near bottom of screen
const float PADDLE_SPEED = 400.0f;     // Pixels per second
const float PADDLE_PART_WIDTH = 15.0f; // Width of each paddle sprite
const float WINDOW_WIDTH = 440.0f;
const float WINDOW_HEIGHT = 660.0f;

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

    ~Paddle() {
        window.removeSprite(leftPart);
        window.removeSprite(middlePart);
        window.removeSprite(rightPart);
    }
};