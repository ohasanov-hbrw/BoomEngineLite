#pragma once

#include "raylib.h"
#include <utils.hpp>
#include <string.h>
#include <filesystem>
#include <memory>

class State;

struct Globals {
    float Scale = 1.0f;
    Vector2 ZeroPoint = {0.f, 0.f};
    Color Background = { 30, 0, 60, 255 };
    int FPS = 60;
    int Width = 640;
    int Height = 480;
    float offset = 45.0f;
    bool MouseInFocus = false;
    Vector2 MousePosition;
    math M;
    Globals() = default;
};

extern Globals G;
