#include <player.hpp>

void MovePlayer(){
    if(IsKeyDown(KEY_A)){
        G.P.a -= 2;
        if(G.P.a < 0){
            G.P.a += 360;
        }
    }
    if(IsKeyDown(KEY_D)){
        G.P.a += 2;
        if(G.P.a > 359){
            G.P.a -= 360;
        }
    }
    float cX = G.M.sin[G.P.a] * 5.0f;
    float cY = G.M.cos[G.P.a] * 5.0f;
    if(IsKeyDown(KEY_W)){
        G.P.x += cX;
        G.P.y += cY;
    }
    if(IsKeyDown(KEY_S)){
        G.P.x -= cX;
        G.P.y -= cY;
    }
    if(IsKeyDown(KEY_E)){
        G.P.x += cY;
        G.P.y -= cX;
    }
    if(IsKeyDown(KEY_Q)){
        G.P.x -= cY;
        G.P.y += cX;
    }
    if(IsKeyDown(KEY_R)){
        G.P.z += 4;
    }
    if(IsKeyDown(KEY_F)){
        G.P.z -= 4;
    }
    if(IsKeyDown(KEY_UP)){
        G.P.l += 2;
    }
    if(IsKeyDown(KEY_DOWN)){
        G.P.l -= 2;
    }
}