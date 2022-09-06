#include <utils.hpp>
#include <globals.hpp>

class Map{
    public:
        Map();
        std::vector<Vector2> vertex;
        std::vector<int> sector;
        void LoadData();
        void UnloadData();
    private:
};