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
                    vertex.push_back(Vector2{cords[i], cords[0]});
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
            if(line[0] == 'p'){
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
                P.x = numbers[0];
                P.y = numbers[1];
                P.a = numbers[2];
                P.curSector = numbers[3];
            }
        }
    }
}

void Map::UnloadData(){

}

void Map::MovePlayer(){
    if(IsKeyDown(KEY_A)){
        P.a -= 3;
        if(P.a < 0){
            P.a += 360;
        }
    }
    if(IsKeyDown(KEY_D)){
        P.a += 3;
        if(P.a > 359){
            P.a -= 360;
        }
    }
    float cX = G.M.sin[P.a] * 0.1f;
    float cY = G.M.cos[P.a] * 0.1f;
    float ccX = 0;
    float ccY = 0;
        if(IsKeyDown(KEY_W)){
        P.x -= cX;
        P.y += cY;
    }
    if(IsKeyDown(KEY_S)){
        P.x += cX;
        P.y -= cY;
    }
    if(IsKeyDown(KEY_E)){
        P.x -= cY;
        P.y -= cX;
    }
    if(IsKeyDown(KEY_Q)){
        P.x += cY;
        P.y += cX;
    }
    if(IsKeyDown(KEY_R)){
        P.z += 4;
    }
    if(IsKeyDown(KEY_F)){
        P.z -= 4;
    }
    if(IsKeyDown(KEY_UP)){
        P.l += 2;
    }
    if(IsKeyDown(KEY_DOWN)){
        P.l -= 2;
    }
    float px = P.x;
    float py = P.y;

    sector temp = sectors[P.curSector];
    for(int s = 0; s < temp.neighbors.size(); s++){
        //std::cout << px << " " << py << " " << sectors[P.curSector].vertex[s].x << " " << sectors[P.curSector].vertex[s].y << "\n";
        if(boxesOverlap(Vector2{P.x, P.y}, Vector2{P.x + ccX, P.y  + ccY}, temp.vertex[s], temp.vertex[s + 1]))
            std::cout <<
                temp.neighbors[s] << " " <<
                (int)boxesOverlap(Vector2{P.x, P.y}, Vector2{P.x + ccX, P.y  + ccY}, temp.vertex[s], temp.vertex[s + 1]) << " " <<
                sideLine(Vector2{P.x + ccX, P.y  + ccY}, temp.vertex[s], temp.vertex[s + 1]) << "\n";
        if(
            temp.neighbors[s] >= 0 &&
            boxesOverlap(Vector2{P.x, P.y}, Vector2{P.x + ccX, P.y  + ccY}, temp.vertex[s], temp.vertex[s + 1]) && 
            sideLine(Vector2{P.x + ccX, P.y  + ccY}, temp.vertex[s], temp.vertex[s + 1]) < 0
        ){
            P.curSector = temp.neighbors[s];
            break;
        }
    }

    P.x += ccX;
    P.y += ccY;
}

void Map::UpdatePlayer(){
    
    /*const struct sector* const sect = &sectors[player.sector];
    const struct xy* const vert = sect->vertex;
    for(unsigned s = 0; s < sect->npoints; ++s)
        if(sect->neighbors[s] >= 0
        && IntersectBox(px,py, px+dx,py+dy, vert[s+0].x, vert[s+0].y, vert[s+1].x, vert[s+1].y)
        && PointSide(px+dx, py+dy, vert[s+0].x, vert[s+0].y, vert[s+1].x, vert[s+1].y) < 0)
        {
            player.sector = sect->neighbors[s];
            break;
        }*/

    
}

Map::player Map::initPlayer(int x, int y, int z, int a, int l){
    player temp;
    temp.x = x;
    temp.y = y;
    temp.z = z;
    temp.a = a;
    temp.l = l;
    return temp;
}