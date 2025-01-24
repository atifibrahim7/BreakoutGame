#include <sdk/window.h>
int main()
{
    SDK::Window window(640, 860, "Craftout");

    SDK::SpriteID ballID = window.createSprite(SDK::SpriteType::Ball, 186, 21);
    SDK::TextID textID = window.createText("Hello World WUWUUW", 20, 10, 10);

    while (window.isOpen())
    {
        window.draw();
    }

    window.removeSprite(ballID);

    return 0;
}
