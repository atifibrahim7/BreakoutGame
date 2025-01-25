#pragma region Brick 
#include <SDK/Window.h>  // Adjust if needed for your SDK include
#include "Ball.h"
const int BRICKS_PER_ROW = 2;
const int BRICK_ROWS = 2;
const float BRICK_WIDTH = 32.0f;
const float BRICK_HEIGHT = 16.0f;
const float BRICK_SPACING = 2.0f;
const float startingYforBricks = 50.0f;
const int incrementPoint = 10;

class Brick {
private:
    SDK::Window& window;
    SDK::SpriteID sprite;
    bool isActive;
    float xPos;    
    float yPos;
public:
    Brick(SDK::Window& gameWindow, float x, float y) :
        window(gameWindow),
        isActive(true),
        xPos(x),
        yPos(y) {
        sprite = window.createSprite(SDK::SpriteType::Brick, x, y);
    }
    bool checkCollision(Ball& ball) {
    float ballX = ball.getX();
    float ballY = ball.getY();
    if (!isActive) return false;

    float ballRight = ballX + 2 * BALL_RADIUS;
    float ballBottom = ballY + 2 * BALL_RADIUS;
    float ballLeft = ballX;
    float ballTop = ballY;

    // Check if ball is overlapping with brick's bounding box
    bool collision = (ballX < xPos + BRICK_WIDTH &&
                      ballRight > xPos &&
                      ballY < yPos + BRICK_HEIGHT &&
                      ballBottom > yPos);

    if (collision) {
        // Determine the side of the brick that the ball hit
        float overlapTop = ballBottom - yPos;
        float overlapBottom = (yPos + BRICK_HEIGHT) - ballTop;
        float overlapLeft = ballRight - xPos;
        float overlapRight = (xPos + BRICK_WIDTH) - ballLeft;

        // Find the smallest overlap to determine the collision side
        float minOverlap = std::min({overlapTop, overlapBottom, overlapLeft, overlapRight});

        if (minOverlap == overlapTop) {
            // Top collision
            ball.reverseY();
        } else if (minOverlap == overlapBottom) {
            // Bottom collision
            ball.reverseY();
        } else if (minOverlap == overlapLeft) {
            // Left collision
            ball.reverseX();
        } else if (minOverlap == overlapRight) {
            // Right collision
            ball.reverseX();
        }

        destroy();  // Destroy the brick after the collision
    }

    return collision;
}

    void destroy() {
        if (isActive) {
            window.removeSprite(sprite);
            isActive = false;
        }
    }

    bool isAlive() const { return isActive; }

    ~Brick() {
        if (isActive) {
            window.removeSprite(sprite);
        }
    }
};
#pragma endregion 


#pragma region BrickManager
static const int ROWS = 5;
static const int COLS = 8;
static const float startingX = 75.0f;
static const float startingY = 50.0f;   
static const float SPACING = 5.0f;   
const int INITIAL_LIVES = 3;
class BrickManager {
private:
    SDK::Window& window;
    SDK::TextID scoreText;
    int score;
    SDK::TextID livesText;
    int lives;
public:
    std::vector<std::unique_ptr<Brick>> bricks;
    BrickManager(SDK::Window& gameWindow) :
        window(gameWindow),
        score(0), lives(INITIAL_LIVES) {

        scoreText = window.createText("Score: 0", 20, 50, 10);
        livesText = window.createText("Lives: " + std::to_string(lives), 20, 300, 10);
        initializeBricks();
    }
    void updateLives() {
        window.updateText(livesText, "Lives: " + std::to_string(lives));
    }
    bool loseLife() {
        lives--;
        updateLives();
        return lives > 0; 
    }

    bool isGameOver() const {
        return lives <= 0;
    }

    void resetLives() {
        lives = INITIAL_LIVES;
        updateLives();
    }
    int getLives() const {
        return lives;
    }
    void initializeBricks() {
        for (int row = 0; row < ROWS; row++) {
            for (int col = 0; col < COLS; col++) {
                float x = startingX + (col * (BRICK_WIDTH + SPACING));
                float y = startingY + (row * (BRICK_HEIGHT + SPACING));

                bricks.push_back(std::make_unique<Brick>(window, x, y));
            }
        }
    }

    void checkCollisions(Ball& ball) {
        bool collisionOccurred = false;

        for (auto& brick : bricks) {
            if (brick && brick->isAlive()) {
                if (brick->checkCollision(ball)) {
                    score += 10;
                    updateScore();
                    //ball.reverseY();  
                    break;  
                }
            }
        }
    }

    void updateScore() {
        window.updateText(scoreText, "Score: " + std::to_string(score));
    }

    bool allBricksDestroyed() const {
		if (bricks.empty()) return true;
		for (const auto& brick : bricks) {
			if (brick && brick->isAlive()) {
				return false;
			}
		}
		return true;
    }

    ~BrickManager() {
        window.removeText(scoreText);
        window.removeText(livesText); 
        bricks.clear();
    }
};

#pragma endregion