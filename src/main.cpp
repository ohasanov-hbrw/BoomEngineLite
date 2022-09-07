#include <math.h>
#include <vector>
#include <algorithm>
#include <utils.hpp>
#include <globals.hpp>
#include <maprender.hpp>
#include "raylib.h"
#include <iostream>

Globals G;

Map map;
int show = 0;

int main() {
    SetTraceLogLevel(LOG_WARNING);
    InitAudioDevice();
	SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(G.Width, G.Height, "BoomEngine");
    SetWindowMinSize(320, 240);
    SetTargetFPS(G.FPS);

    G.M = initMath();
    map.P.a = 0;
    map.P.x = 0;
    map.P.y = 0;
    map.P.z = 0;
    map.P.l = 0;

    map.LoadData();

    std::cout << "Loaded " << map.vertex.size() << " vertex positions and " << map.sectors.size() << " sectors\n";
    while(!WindowShouldClose()){
        map.MovePlayer();
        GetScale();
        GetMouse();
        BeginDrawing();
            ClearBackground(BLACK);
            DrawText(TextFormat("X: %f", map.P.x), ScaleCordX(0), ScaleCordY(0), Scale(16), WHITE);
            DrawText(TextFormat("Y: %f", map.P.y), ScaleCordX(0), ScaleCordY(20), Scale(16), WHITE);
            DrawText(TextFormat("Z: %f", map.P.z), ScaleCordX(0), ScaleCordY(40), Scale(16), WHITE);
            DrawText(TextFormat("A: %d", map.P.a), ScaleCordX(0), ScaleCordY(60), Scale(16), WHITE);
            DrawText(TextFormat("L: %d", map.P.l), ScaleCordX(0), ScaleCordY(80), Scale(16), WHITE);
            DrawText(TextFormat("S: %d", map.P.curSector), ScaleCordX(0), ScaleCordY(100), Scale(16), WHITE);
            DrawCircleV(ScaleCords(Vector2{320, 240}), Scale(5), GREEN);
            DrawLineEx(ScaleCords(Vector2{320, 240}), ScaleCords(Vector2{(320 + 7 * G.M.cos[(map.P.a + 90) % 360]), (240 + 7 * G.M.sin[(map.P.a + 90) % 360])}), Scale(3), BLUE);
            
            Color colorPicker[8] = {RED, GREEN, BLUE, WHITE, YELLOW, MAGENTA, GRAY, PURPLE};
            for(int i = 0; i < map.sectors.size(); i++){
                for(int j = 1; j < map.sectors[i].vertex.size(); j++){
                    if(i == map.P.curSector){
                        DrawLineEx(
                            ScaleCords((map.sectors[i].vertex[j - 1] + Vector2{-map.P.x, -map.P.y}) * Vector2{30, 30} + Vector2{320, 240}),
                            ScaleCords((map.sectors[i].vertex[j] + Vector2{-map.P.x, -map.P.y}) * Vector2{30, 30} + Vector2{320, 240}),
                            Scale(4),
                            colorPicker[i % 8]
                        );
                        DrawCircleV((ScaleCords((map.sectors[i].vertex[j] + Vector2{-map.P.x, -map.P.y}) * Vector2{30, 30} + Vector2{320, 240})), Scale(3), RED);
                    }
                    else if(map.sectors[map.P.curSector].floor == map.sectors[i].floor){
                        DrawLineEx(
                            ScaleCords((map.sectors[i].vertex[j - 1] + Vector2{-map.P.x, -map.P.y}) * Vector2{30, 30} + Vector2{320, 240}),
                            ScaleCords((map.sectors[i].vertex[j] + Vector2{-map.P.x, -map.P.y}) * Vector2{30, 30} + Vector2{320, 240}),
                            Scale
                            (4),
                            Fade(WHITE, 0.2f)
                        );
                        DrawCircleV((ScaleCords((map.sectors[i].vertex[j] + Vector2{-map.P.x, -map.P.y}) * Vector2{30, 30} + Vector2{320, 240})), Scale(3), Fade(WHITE, 0.2f));
                    }
                }
            }
            //DrawCircleV((ScaleCords((map.useless2 + Vector2{-map.P.x, -map.P.y}) * Vector2{30, 30} + Vector2{320, 240})), Scale(3), BLACK);
        EndDrawing();
    }

    CloseWindow();
}

