#include <maprender.hpp>

Map::Map(){

}

void Map::LoadData(){
    std::ifstream ifs("resources/map.txt");
	std::string line;
	if (ifs.is_open()){
		while(std::getline(ifs, line)){
            if(line[0] == 'v'){
                line.push_back(' ');
                std::vector<int> cords;
                int last = 0;
                bool isLastDigit = false;
                for(int i = 0; i < line.size(); i++){
                    if(isdigit(line[i])){
                        if(!isLastDigit){
                            last = i;
                            isLastDigit = true;
                        }
                    }
                    else{
                        if(isLastDigit == true){
                            std::string number = line.substr(last, i - last);
                            cords.push_back(stoi(number));
                        }
                        last = i;
                        isLastDigit = false;
                    }
                }
                for(int i = 1; i < cords.size(); i++){
                    vertex.push_back(Vector2{cords[0], cords[i]});
                }
            }
        }
    }
}

void Map::UnloadData(){

}