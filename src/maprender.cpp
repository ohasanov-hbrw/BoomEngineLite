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
                std::vector<float> cords;
                int last = 0;
                bool isLastDigit = false;
                for(int i = 0; i < line.size(); i++){
                    if(isdigit(line[i]) || line[i] == '-'  || line[i] == '.'){
                        if(!isLastDigit){
                            last = i;
                            isLastDigit = true;
                        }
                    }
                    else{
                        if(isLastDigit == true){
                            std::string number = line.substr(last, i - last);
                            cords.push_back(stof(number));
                        }
                        last = i;
                        isLastDigit = false;
                    }
                }
                for(int i = 1; i < cords.size(); i++){
                    vertex.push_back(Vector2{cords[0], cords[i]});
                }
            }
            if(line[0] == 's'){
                line.push_back(' ');
                std::vector<float> numbers;
                int last = 0;
                bool isLastDigit = false;
                for(int i = 0; i < line.size(); i++){
                    if(isdigit(line[i]) || line[i] == '-'  || line[i] == '.'){
                        if(!isLastDigit){
                            last = i;
                            isLastDigit = true;
                        }
                    }
                    else{
                        if(isLastDigit == true){
                            std::string number = line.substr(last, i - last);
                            numbers.push_back(stof(number));
                        }
                        last = i;
                        isLastDigit = false;
                    }
                }
                sector tempSector;
                tempSector.floor = numbers[0];
                tempSector.ceiling = numbers[1];
                int index = 0;
                tempSector.vertex.push_back(Vector2{0,0});
                for(int i = 2; i < numbers.size(); i++){
                    index++;
                    if(index <= (numbers.size() - 2) / 2){
                        tempSector.vertex.push_back(vertex[(int)numbers[i]]);
                    }
                    else{
                        tempSector.neighbors.push_back((int)numbers[i]);
                    }
                }
                tempSector.vertex[0] = tempSector.vertex[tempSector.vertex.size() - 1];
                sectors.push_back(tempSector);
            }
        }
    }
}

void Map::UnloadData(){

}