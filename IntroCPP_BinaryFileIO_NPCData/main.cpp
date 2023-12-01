/*******************************************************************************************
*
*   raylib [core] example - Basic window
*
*   Welcome to raylib!
*
*   To test examples, just press F6 and execute raylib_compile_execute script
*   Note that compiled executable is placed in the same folder as .c file
*
*   You can find all basic examples on C:\raylib\raylib\examples folder or
*   raylib official webpage: www.raylib.com
*
*   Enjoy using raylib. :)
*
*   This example has been created using raylib 1.0 (www.raylib.com)
*   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
*
*   Copyright (c) 2014 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include "raylib.h"
#include "DataFile.h"
#include <iostream>

int main(int argc, char* argv[])
{
    // Initialization
    //--------------------------------------------------------------------------------------
    int screenWidth = 800;
    int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

    DataFile data;
    int currentRecordIdx = 0;

    data.Load("npc_data.dat");

    DataFile::Record* currentRecord = data.GetRecord(currentRecordIdx);
    if (currentRecord != nullptr) exit;
    Texture2D recordTexture = LoadTextureFromImage(currentRecord->image);
    UnloadImage(currentRecord->image);

    SetTargetFPS(60);
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        //----------------------------------------------------------------------------------

        if (IsKeyPressed(KEY_LEFT)) // View Previous Record
        {
            currentRecordIdx--;
            if (currentRecordIdx < 0) // Ensure the user cannot view previous record if there isn't one
            {
                currentRecordIdx = 0;
            }
            delete currentRecord;
            UnloadTexture(recordTexture);
            currentRecord = data.GetRecord(currentRecordIdx);
            recordTexture = LoadTextureFromImage(currentRecord->image);
            UnloadImage(currentRecord->image);
            std::cout << currentRecord->name << std::endl;
        }

        if (IsKeyPressed(KEY_RIGHT)) // View Next Record
        {
            currentRecordIdx++;
            if (currentRecordIdx >= data.GetRecordCount()) // Ensure the user cannot view next record if there isn't one
            {
                currentRecordIdx = data.GetRecordCount() - 1;
            }
            delete currentRecord;
            UnloadTexture(recordTexture);
            currentRecord = data.GetRecord(currentRecordIdx);
            recordTexture = LoadTextureFromImage(currentRecord->image);
            UnloadImage(currentRecord->image);
            std::cout << currentRecord->name << std::endl;
        }


        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(RAYWHITE);

        DrawTexture(recordTexture, 300, 50, WHITE);

        DrawText("NAME", 10, 50, 20, LIGHTGRAY);
        DrawText(currentRecord->name.c_str(), 10, 80, 20, LIGHTGRAY);

        DrawText("AGE", 10, 120, 20, LIGHTGRAY);
        DrawText(to_string(currentRecord->age).c_str(), 10, 150, 20, LIGHTGRAY);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    UnloadTexture(recordTexture);
    
    // De-Initialization
    //--------------------------------------------------------------------------------------   
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}