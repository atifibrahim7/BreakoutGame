#include <catch2/catch_session.hpp>
#include <catch2/catch_test_macros.hpp>

#include <sdk/window.h>

TEST_CASE("SDK_SPRITES", "Verify SDK sprites API") {
    SDK::Window window(10, 10, "Test");
    auto id = window.createSprite(SDK::SpriteType::Ball, 0, 0);
    
    SECTION("Test ball sprite") {
        REQUIRE(window.countValidSprites() == 1);
        REQUIRE(window.isValidSprite(id));
        REQUIRE(!window.isValidSprite(id + 1));
        REQUIRE(window.moveSprite(id, 1, 1) == SDK::Result::Success);
        window.removeSprite(id);
        REQUIRE(window.countValidSprites() == 0);
        REQUIRE(!window.isValidSprite(id));
        REQUIRE(window.moveSprite(id, 1, 1) == SDK::Result::InvalidID);
        window.removeSprite(id);
        REQUIRE(window.countValidSprites() == 0);
    }

    SECTION("Test moving Ball Sprite") {
        // remove the id sprite, for test section
        window.removeSprite(id);

        auto newID = window.createSprite(SDK::SpriteType::Ball, 0, 0);
        REQUIRE(window.countValidSprites() == 1);
        REQUIRE(window.isValidSprite(newID));
        REQUIRE(!window.isValidSprite(id));
        REQUIRE(window.moveSprite(id, 1, 1) == SDK::Result::InvalidID);
        REQUIRE(window.moveSprite(newID, 1, 1) == SDK::Result::Success);
        window.removeSprite(newID);
        REQUIRE(window.countValidSprites() == 0);
        REQUIRE(!window.isValidSprite(newID));
        REQUIRE(window.moveSprite(newID, 1, 1) == SDK::Result::InvalidID);
        window.removeSprite(newID);
        REQUIRE(window.countValidSprites() == 0);
    }

    SECTION("Test Add-remove more sprites", "validating the sprite count during adding and removing") {
        // remove the id sprite, for test section
        window.removeSprite(id);

        auto id2 = window.createSprite(SDK::SpriteType::Ball, 0, 0);
        REQUIRE(window.countValidSprites() == 1);
        auto id3 = window.createSprite(SDK::SpriteType::Ball, 0, 0);
        REQUIRE(window.countValidSprites() == 2);
        auto id4 = window.createSprite(SDK::SpriteType::Ball, 0, 0);
        REQUIRE(window.countValidSprites() == 3);
        auto id5 = window.createSprite(SDK::SpriteType::Ball, 0, 0);
        REQUIRE(window.countValidSprites() == 4);

        window.removeSprite(id2);
        REQUIRE(window.countValidSprites() == 3);
        window.removeSprite(id4);
        REQUIRE(window.countValidSprites() == 2);

        auto id6 = window.createSprite(SDK::SpriteType::Ball, 0, 0);
        REQUIRE(window.countValidSprites() == 3);
        auto id7 = window.createSprite(SDK::SpriteType::Ball, 0, 0);
        REQUIRE(window.countValidSprites() == 4);

        window.removeSprite(id3);
        REQUIRE(window.countValidSprites() == 3);
        window.removeSprite(id5);
        REQUIRE(window.countValidSprites() == 2);
        window.removeSprite(id6);
        REQUIRE(window.countValidSprites() == 1);
        window.removeSprite(id7);
        REQUIRE(window.countValidSprites() == 0);
    }
}

TEST_CASE("TEST_TEXT", "Verify SDK text working"){
    REQUIRE(true);
}


int main( int argc, char* argv[] ) {
  // (optional) setup code
  int result = Catch::Session().run( argc, argv );

  // (optional) cleanup code
  return result;
}

