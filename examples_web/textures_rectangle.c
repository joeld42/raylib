/*******************************************************************************************
*
*   raylib [core] example - Texture loading and drawing a part defined by a rectangle (adapted for HTML5 platform)
*
*   This example has been created using raylib 1.3 (www.raylib.com)
*   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
*
*   Copyright (c) 2015 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include "raylib.h"

#if defined(PLATFORM_WEB)
    #include <emscripten/emscripten.h>
#endif

//----------------------------------------------------------------------------------
// Global Variables Definition
//----------------------------------------------------------------------------------
int screenWidth = 800;
int screenHeight = 450;

// NOTE: Textures MUST be loaded after Window initialization (OpenGL context is required)
Texture2D guybrush;

Vector2 position;
Rectangle frameRec;

int currentFrame = 0;

//----------------------------------------------------------------------------------
// Module Functions Declaration
//----------------------------------------------------------------------------------
void UpdateDrawFrame(void);     // Update and Draw one frame

//----------------------------------------------------------------------------------
// Main Enry Point
//----------------------------------------------------------------------------------
int main()
{
    // Initialization
    //--------------------------------------------------------------------------------------
    InitWindow(screenWidth, screenHeight, "raylib [texture] example - texture rectangle");
   
    guybrush = LoadTexture("resources/guybrush.png");        // Texture loading
    position = (Vector2){ 350.0f, 240.0f };
    // NOTE: On PLATFORM_WEB, NPOT textures support is limited
    frameRec = (Rectangle){ 0, 0, guybrush.width/7, guybrush.height };
    
#if defined(PLATFORM_WEB)
    emscripten_set_main_loop(UpdateDrawFrame, 0, 1);
#else
    SetTargetFPS(60);   // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------
    
    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        UpdateDrawFrame();
    }
#endif

    // De-Initialization
    //--------------------------------------------------------------------------------------
    UnloadTexture(guybrush);       // Texture unloading
    
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}

//----------------------------------------------------------------------------------
// Module Functions Definition
//----------------------------------------------------------------------------------
void UpdateDrawFrame(void)
{
    // Update
    //----------------------------------------------------------------------------------
    if (IsKeyPressed(KEY_RIGHT))
    {        
        currentFrame++;
        
        if (currentFrame > 6) currentFrame = 0;
        
        frameRec.x = currentFrame*guybrush.width/7;
    }
    //----------------------------------------------------------------------------------

    // Draw
    //----------------------------------------------------------------------------------
    BeginDrawing();

        ClearBackground(RAYWHITE);

        DrawTexture(guybrush, 35, 40, WHITE);
        DrawRectangleLines(35, 40, guybrush.width, guybrush.height, LIME);
        
        DrawTextureRec(guybrush, frameRec, position, WHITE);  // Draw part of the texture
        
        DrawRectangleLines(35 + frameRec.x, 40 + frameRec.y, frameRec.width, frameRec.height, RED);
        
        DrawText("PRESS RIGHT KEY to", 540, 310, 10, GRAY);
        DrawText("CHANGE DRAWING RECTANGLE", 520, 330, 10, GRAY);
        
        DrawText("Guybrush Ulysses Threepwood,", 100, 300, 10, GRAY);
        DrawText("main character of the Monkey Island series", 80, 320, 10, GRAY);
        DrawText("of computer adventure games by LucasArts.", 80, 340, 10, GRAY);

    EndDrawing();
    //----------------------------------------------------------------------------------
}