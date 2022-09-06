#include <maprender.hpp>

Map::Map(){

}

Map::LoadData(){
    std::ifstream ifs("resources/map.txt");
	std::string line;
	if (ifs.is_open()){
		while(std::getline(ifs, line)){
            if(line[0] == 'v'){
                
            }
        }
    }
}