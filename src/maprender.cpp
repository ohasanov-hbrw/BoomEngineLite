#include <maprender.hpp>

Map::Map(){

}

void Map::LoadData(){
    std::ifstream ifs("resources/map.txt");
	std::string line;
    useless = (Vector2*)malloc(sizeof(Vector2));
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
        ccX = -cX;
        ccY = cY;
    }
    if(IsKeyDown(KEY_S)){
        ccX = cX;
        ccY = -cY;
    }
    if(IsKeyDown(KEY_E)){
        ccX = -cY;
        ccY = -cX;
    }
    if(IsKeyDown(KEY_Q)){
        ccX = cY;
        ccY = cX;
    }
    if(IsKeyDown(KEY_R)){
        P.z += 1;
    }
    if(IsKeyDown(KEY_F)){
        P.z -= 1;
    }
    if(IsKeyDown(KEY_UP)){
        P.l += 2;
    }
    if(IsKeyDown(KEY_DOWN)){
        P.l -= 2;
    }


    sector temp = sectors[P.curSector];

    for(int s = 0; s < temp.neighbors.size(); s++){
        float x1 = temp.vertex[s].x;
        float x2 = temp.vertex[s+1].x;
        float y1 = temp.vertex[s].y;
        float y2 = temp.vertex[s+1].y;
        
        float k1 = ((y2-y1) * (P.x + ccX-x1) - (x2-x1) * (P.y + ccY-y1)) / (std::pow((y2-y1),2) + std::pow((x2-x1),2));
        float x41 = P.x + ccX- k1 * (y2-y1);
        float y41 = P.y + ccY+ k1 * (x2-x1);
        //useless2 = Vector2{x4, y4};

        if(
            CheckCollisionLines(Vector2{P.x, P.y}, Vector2{x41, y41}, temp.vertex[s], temp.vertex[s + 1], useless)// &&
            //CheckCollisionPointCircle(*useless, Vector2{P.x + ccX, P.y  + ccY}, 0.12f)
            //(float)sideLine(Vector2{P.x + ccX, P.y  + ccY}, temp.vertex[s], temp.vertex[s + 1]) < 0.0f
            //true
        ){
            float hole_low  = temp.neighbors[s] < 0 ?  9e9 : std::max(temp.floor, sectors[temp.neighbors[s]].floor);
            float hole_high = temp.neighbors[s] < 0 ? -9e9 : std::min(temp.ceiling, sectors[temp.neighbors[s]].ceiling);
            //std::cout << hole_low << " " << hole_high << "\n";
            if(hole_high < P.z+10 || hole_low  > P.z+2)
            {
                //if(CheckCollisionPointCircle(useless2, Vector2{P.x + ccX, P.y  + ccY}, 0.2f)){
                    //std::cout << "amogus\n";
                    float dx = ccX;
                    float dy = ccY;
                    float xd = temp.vertex[s+1].x - temp.vertex[s].x;
                    float yd = temp.vertex[s+1].y - temp.vertex[s].y;
                    dx = xd * (dx*xd + yd*dy) / (xd*xd + yd*yd);
                    dy = yd * (dx*xd + yd*dy) / (xd*xd + yd*yd);
                    
                    float m_A = temp.vertex[s].y - temp.vertex[s+1].y;
                    float m_B = temp.vertex[s+1].x - temp.vertex[s].x;
                    float m_C = temp.vertex[s].x * temp.vertex[s+1].y - temp.vertex[s+1].x * temp.vertex[s].y;

                    float dist = std::abs(m_A * (P.x + ccX) + m_B * (P.y + ccY) + m_C) * Q_rsqrt(m_A * m_A + m_B * m_B);
                    
                    float k = ((y2-y1) * (P.x + ccX-x1) - (x2-x1) * (P.y + ccY-y1)) / (std::pow((y2-y1),2) + std::pow((x2-x1),2));
                    float x4 = P.x + ccX- k * (y2-y1);
                    float y4 = P.y + ccY+ k * (x2-x1);
                    useless2 = Vector2{x4, y4};

                    std::cout << m_C << " " << m_A  << " " << m_B << "\n";
                    //ccX = dx;
                    //ccY = dy;

                    if(dist < 0.9f){
                        
                        //ccX += (0.06f / dist) * ((P.x) - x4);
                        //ccY += (0.06f / dist) * ((P.y) - y4);
                        //ccX = 0;
                        //ccY = 0;
                        std::cout << "amog" << " " << ccX  << " " << ccY << "\n";
                    }

                    /*if(CheckCollisionPointCircle(useless2, Vector2{P.x + ccX, P.y  + ccY}, 0.2f)){
                        ccX = 0;
                        ccY = 0;
                    }*/
                //}

            }
        }

    }

    

    for(int s = 0; s < temp.neighbors.size(); s++){
        if(
            temp.neighbors[s] >= 0 &&
            /*boxesOverlap(Vector2{P.x, P.y}, Vector2{P.x + ccX, P.y  + ccY}, temp.vertex[s], temp.vertex[s + 1])*/
            CheckCollisionLines(Vector2{P.x, P.y}, Vector2{P.x + ccX, P.y  + ccY}, temp.vertex[s], temp.vertex[s + 1], useless) && 
            sideLine(Vector2{P.x + ccX, P.y  + ccY}, temp.vertex[s], temp.vertex[s + 1]) < 0
        ){
            P.curSector = temp.neighbors[s];
            P.z = sectors[temp.neighbors[s]].floor;
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
void Map::RenderScreen(){
    
}