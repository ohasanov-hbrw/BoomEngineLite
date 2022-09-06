#include <math.h>
#include <vector>
#include <algorithm>
#include <utils.hpp>
#include <player.hpp>
#include <globals.hpp>
#include <maprender.hpp>
#include "raylib.h"
#include <iostream>

Globals G;

Map map;

int main() {
    SetTraceLogLevel(LOG_WARNING);
    InitAudioDevice();
	SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(G.Width, G.Height, "BoomEngine");
    SetWindowMinSize(320, 240);
    SetTargetFPS(G.FPS);

    G.M = initMath();
    G.P.a = 0;
    G.P.x = 0;
    G.P.y = 0;
    G.P.z = 0;
    G.P.l = 0;

    map.LoadData();

    while(!WindowShouldClose()){
        MovePlayer();
        GetScale();
        GetMouse();
        BeginDrawing();
            ClearBackground(BLACK);
            DrawText(TextFormat("X: %d", G.P.x), ScaleCordX(0), ScaleCordY(0), Scale(16), WHITE);
            DrawText(TextFormat("Y: %d", G.P.y), ScaleCordX(0), ScaleCordY(20), Scale(16), WHITE);
            DrawText(TextFormat("Z: %d", G.P.z), ScaleCordX(0), ScaleCordY(40), Scale(16), WHITE);
            DrawText(TextFormat("A: %d", G.P.a), ScaleCordX(0), ScaleCordY(60), Scale(16), WHITE);
            DrawText(TextFormat("L: %d", G.P.l), ScaleCordX(0), ScaleCordY(80), Scale(16), WHITE);
            DrawText(TextFormat("S: %f", Scale(5)), ScaleCordX(0), ScaleCordY(100), Scale(16), WHITE);
            DrawText(TextFormat("G: %f", G.Scale), ScaleCordX(0), ScaleCordY(120), Scale(16), WHITE);
        EndDrawing();
    }

    CloseWindow();
}

