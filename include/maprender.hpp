#include <utils.hpp>
#include <globals.hpp>
#include <string.h>
#include <fstream>
#include <iostream>

class Map{
    public:
        Map();
        struct sector{
            int floor;
            int ceiling;
            std::vector<int> neighbors;
            std::vector<Vector2> vertex;
        };
        std::vector<Vector2> vertex;
        std::vector<sector> sectors;
        void LoadData();
        void UnloadData();
    private:
};