#include <math.h>
#include <vector>
#include <algorithm>
#include <utils.hpp>
#include "raylib.h"
#include <iostream>

int main() {
    SetTraceLogLevel(LOG_WARNING);
    InitAudioDevice();
	SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(Global.Width, Global.Height, "BoomEngine");
    SetWindowMinSize(320, 240);
    SetTargetFPS(72);
    while(!WindowShouldClose()){
        BeginDrawing();

        ClearBackground(Global.Background);
        EndDrawing();
    }

    CloseWindow();
}

