#include <utils.hpp>
#include <globals.hpp>
#include <string.h>
#include <fstream>
#include <iostream>

class Map{
    public:
        Map();
        std::vector<Vector2> vertex;
        std::vector<int> sector;
        void LoadData();
        void UnloadData();
    private:
};