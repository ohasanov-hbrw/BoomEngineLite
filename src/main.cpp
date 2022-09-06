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
    std::cout << "Loaded " << map.vertex.size() << " vertex positions and " << map.sectors.size() << " sectors\n";
    while(!WindowShouldClose()){
        MovePlayer();
        GetScale();
        GetMouse();
        BeginDrawing();
            ClearBackground(BLACK);
            DrawText(TextFormat("X: %f", G.P.x), ScaleCordX(0), ScaleCordY(0), Scale(16), WHITE);
            DrawText(TextFormat("Y: %f", G.P.y), ScaleCordX(0), ScaleCordY(20), Scale(16), WHITE);
            DrawText(TextFormat("Z: %f", G.P.z), ScaleCordX(0), ScaleCordY(40), Scale(16), WHITE);
            DrawText(TextFormat("A: %d", G.P.a), ScaleCordX(0), ScaleCordY(60), Scale(16), WHITE);
            DrawText(TextFormat("L: %d", G.P.l), ScaleCordX(0), ScaleCordY(80), Scale(16), WHITE);
            DrawText(TextFormat("S: %f", Scale(5)), ScaleCordX(0), ScaleCordY(100), Scale(16), WHITE);
            DrawText(TextFormat("G: %f", G.Scale), ScaleCordX(0), ScaleCordY(120), Scale(16), WHITE);
            DrawCircleV(ScaleCords(Vector2{320, 240}), Scale(5), GREEN);
            DrawLineEx(ScaleCords(Vector2{320, 240}), ScaleCords(Vector2{(320 + 7 * G.M.cos[(G.P.a + 90) % 360]), (240 + 7 * G.M.sin[(G.P.a + 90) % 360])}), Scale(3), BLUE);
            
            Color colorPicker[8] = {RED, GREEN, BLUE, WHITE, YELLOW, MAGENTA, GRAY, PURPLE};
            for(int i = 0; i < map.sectors.size(); i++){
                for(int j = 1; j < map.sectors[i].vertex.size(); j++){
                    DrawLineEx(
                        ScaleCords(map.sectors[i].vertex[j - 1] * Vector2{10, 10} + Vector2{G.P.x, -G.P.y}  + Vector2{320, 240}),
                        ScaleCords(map.sectors[i].vertex[j] * Vector2{10, 10} + Vector2{G.P.x, -G.P.y}  + Vector2{320, 240}),
                        Scale(4),
                        colorPicker[i % 8]
                    );
                }
            }
            for(int i = 0; i < map.vertex.size(); i++){
                DrawCircleV((ScaleCords(map.vertex[i] * Vector2{10, 10} + Vector2{G.P.x, -G.P.y}  + Vector2{320, 240})), Scale(5), RED);
            }

        EndDrawing();
    }

    CloseWindow();
}

