#include "game.h"
#include "surface.h"

#include <cstdio> //printf
#include <iostream>

namespace Tmpl8
{
    // -----------------------------------------------------------
    // Initialize the application
    // -----------------------------------------------------------
    void Game::Init()
    {
    }

    // -----------------------------------------------------------
    // Close down application
    // -----------------------------------------------------------
    void Game::Shutdown()
    {
    }

    // -----------------------------------------------------------
    // Process keyboard input
    // ----------------------------------------------------------
    void Game::ProcessInput()
    {
        // Update key states
        pressed = keys & ~held; // keys that are currently down but were not down in the previous tick
        released = ~keys & held; // keys that were down in the previous tick but are not down now
        held = keys; // update prevKeys for the next tick
    }


    static Sprite rotatingGun(new Surface("assets/aagun.tga"), 36);
    static int frame = 0;

    // -----------------------------------------------------------
    // Main application tick function
    // -----------------------------------------------------------
    void Game::Tick(float deltaTime)
    {
        // Call this once per tick.
        ProcessInput();

        // Handle input.
        if (GetKey(SDL_SCANCODE_W))
        {
            std::cout << "W" << std::endl;
        }
        if (GetKey(SDL_SCANCODE_A))
        {
            std::cout << "A" << std::endl;
        }
        if (GetKey(SDL_SCANCODE_S))
        {
            std::cout << "S" << std::endl;
        }
        if (GetKey(SDL_SCANCODE_D))
        {
            std::cout << "D" << std::endl;
        }

        // clear the graphics window
        screen->Clear(0);
        // print something in the graphics window
        screen->Print("hello world", 2, 2, 0xffffff);
        // print something to the text window
        // printf("this goes to the console window.\n");
        // draw a sprite
        rotatingGun.SetFrame(frame);
        rotatingGun.Draw(screen, 100, 100);
        if (++frame == 36) frame = 0;
    }
};