#pragma once
#include "raylib.h"
#include <string>
#include <vector>
#include <cstdio>
#include <iostream>
#include <ctime>

#define RAYMATH_IMPLEMENTATION
# define M_PI 3.14159265358979323846f
//extern "C" {
    #include "raymath.h"
//}




void GetScale();
//Get the absolute Mouse position
void GetMouse(); //No Tom, you will never be able to catch Jerry :'(
//Scale a number based on the current scaling factor
float Scale(float);

//Scale a Rectangle based on the current scaling factor
Rectangle ScaleRect(Rectangle);
//Scale a Vector based on the current scaling factor and also add the origin offset
Vector2 ScaleCords(Vector2);

//Scale the X position and add the origin offset
float ScaleCordX(float);
//Scale the Y position and add the origin offset
float ScaleCordY(float);

//Get the center point of a rectangle
Vector2 GetCenter(Rectangle);
//Get the "origin" of a rectangle for raylib drawing functions and return a vector
Vector2 GetRaylibOrigin(Rectangle);
//Get the "origin" of a rectangle for raylib drawing functions and return a rectangle
Rectangle GetRaylibOriginR(Rectangle);

//Clip a number between two other numbers
float clip( float, float, float);
//Interpolate more points in between two points
Vector2 lerp(Vector2, Vector2, float);
//Return a vector with both of the cordinates set to a float
Vector2 vectorize(float);
//Calculate the distance between two points
float distance(Vector2 &, Vector2 &);
//Binary search algorithm
int Search(std::vector<float>, float,int,int);

Vector2 getPointOnCircle(float, float, float, float);

std::string getSampleSetFromInt(int);

//Add extra operators because raylib sucks
inline Vector2 operator + (Vector2 p0, Vector2 p1){
    return Vector2Add(p0, p1);
}

inline Vector2 operator - (Vector2 p0, Vector2 p1){
    return Vector2Subtract(p0, p1);
}

inline Vector2 operator * (Vector2 p0, Vector2 p1){
    return Vector2Multiply(p0, p1);
}

inline Vector2 operator / (Vector2 p0, Vector2 p1){
    return Vector2Divide(p0, p1);
}

typedef struct{
    float cos[360];
    float sin[360];
    float pi = M_PI;
}math; 

math initMath();

float vectorCrossProduct(Vector2, Vector2);
bool rangesOverlap(float, float, float, float);
bool boxesOverlap(Vector2, Vector2, Vector2, Vector2);
float sideLine(Vector2, Vector2, Vector2);
float Q_rsqrt(float);