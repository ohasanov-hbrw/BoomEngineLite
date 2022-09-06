#include <utils.hpp>
#include <cmath>
#include <vector>
#include <algorithm>
#include <globals.hpp>
#include <iostream>
#include <ctype.h>

void GetScale(){
    //Get the scale and also get the current offset for the zero point of the game area
    G.Scale = std::min(GetScreenWidth()/640.0f, GetScreenHeight()/480.0f);
    G.ZeroPoint = {GetScreenWidth() / 2.0f - (G.Scale * 320.0f), GetScreenHeight() / 2.0f - (G.Scale * 240.0f)};
}

void GetMouse(){
    //Get the mouse position and also check if it is in the game area
    G.MouseInFocus = CheckCollisionPointRec(GetMousePosition(), (Rectangle){0, 0, GetScreenWidth(), GetScreenHeight()});
    if(!G.MouseInFocus){
        G.MousePosition = {0,0};
    }
    else {
        G.MousePosition = {(GetMouseX() - G.ZeroPoint.x) / G.Scale, (GetMouseY() - G.ZeroPoint.y) / G.Scale};
    }
}

float Scale(float a){
    //Basic scaling function
    return a * G.Scale;
}

Rectangle ScaleRect(Rectangle a){
    //Scale the size and also move the rectangle depending on the offset
    return {a.x * G.Scale + G.ZeroPoint.x, a.y * G.Scale + G.ZeroPoint.y, a.width * G.Scale, a.height * G.Scale};
}

Vector2 ScaleCords(Vector2 a){
    //Scale so that the coordinates are correct for our window size and also move them based on the offset
    return {a.x * G.Scale + G.ZeroPoint.x, a.y * G.Scale + G.ZeroPoint.y};
}

float ScaleCordX(float a){
    //Do the same thing as the ScaleCords function but only for the x axis
    return a * G.Scale + G.ZeroPoint.x;
}

float ScaleCordY(float a){
    //Do the same thing as the ScaleCords function but only for the y axis
    return a * G.Scale + G.ZeroPoint.y;
}

Vector2 GetCenter(Rectangle a){
    //Get the center of a rectangle
    return {a.x + a.width / 2, a.y + a.height / 2};
}
Vector2 GetRaylibOrigin(Rectangle a){
    //Move the coordinates so that the center of the rectangle is where we want it to be for the rendering process
    return {a.x - a.width / 2, a.y - a.height / 2};
}

Rectangle GetRaylibOriginR(Rectangle a){
    //Do the same thing as the RaylibOrigin function but this time just take the whole rectangle
    return {a.x - a.width / 2, a.y - a.height / 2, a.width, a.height};
}

float clip( float n, float lower, float upper ){
    //I have no idea what this does but it works
    n = ( n > lower ) * n + !( n > lower ) * lower;
    return ( n < upper ) * n + !( n < upper ) * upper;
}

Vector2 lerp(Vector2 a, Vector2 b, float t){
    //Thank you geeksforgeeks
    return { .x = (1 - t) * a.x + t * b.x, .y = (1 - t) * a.y + t * b.y};
}



Vector2 vectorize(float i) {
    //Really dumb but raylib needs it
    return Vector2{i, i};
}

float distance(Vector2 &p0, Vector2 &p1){
    //Its a bit heavy of a process but we dont do this frequently anyway
    return std::sqrt(std::pow(std::abs(p0.x - p1.x),2) + std::pow(std::abs(p0.y - p1.y),2));
}

int Search(std::vector<float> arr, float x,int l,int r) {
    //Basic binary search implementation
    if (r >= l) {
        int mid = (l + r) / 2;
        if (arr[mid] == x || l==r)
            return mid;
        if (arr[mid] > x)
            return Search(arr, x,l, mid - 1);
        else 
            return Search(arr, x,mid + 1, r);
    }
    else
        return l;
}


math initMath(){
    math temp;
    for(int i = 0; i < 360; i++){
        temp.cos[i] = cos(i / 180.0*M_PI);
        temp.sin[i] = sin(i / 180.0*M_PI);
    }
    return temp;
}

float vectorCrossProduct(Vector2 a, Vector2 b){
    return ((a.x)*(b.y) - (b.x)*(a.y));
}

bool rangesOverlap(float a0, float a1, float b0, float b1){
    return (std::min(a0,a1) <= std::max(b0,b1) && std::min(b0,b1) <= std::max(a0,a1));
}

bool boxesOverlap(Vector2 a, Vector2 b, Vector2 c, Vector2 d){
    return (rangesOverlap(a.x,b.x,c.x,d.x) && rangesOverlap(a.y,b.y,c.y,d.y));
}

int sideLine(Vector2 p, Vector2 a, Vector2 b){
    return vectorCrossProduct(b - a, p - a);
}