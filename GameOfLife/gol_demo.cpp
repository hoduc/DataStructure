#include <iostream>
#include <fstream>

enum STATE{DEAD, LIVE};

struct cell{
	STATE NOW;
	STATE FUTURE;
	cell():NOW(DEAD),FUTURE(DEAD){};
};

cell **map;
int row = 0;
int col = 0;

void setup(){
	std::fstream im;		//input map
	//read in row and column
	im.open("map.txt", std::ios::in);
	
	im >> row >> col;
	map = new cell*[row];
	for (int i = 0; i < row; ++i){
		map[i] = new cell[col];
	}

	im.seekg(col, std::ios::beg);
	for (int i = 0; i < row; ++i){
		for (int j = 0; j < col; ++j){
			char c = im.get();
			if (c == '*')
				map[i][j].NOW = LIVE;
			else if (c == ' ')
				map[i][j].NOW = DEAD;
		}
		im.get();
	}
	
}

void draw(){
	for (int i = 0; i < row; ++i){
		for (int j = 0; j < col; ++j){
			if (map[i][j].NOW == DEAD){
				std::cout << " ";
			}
			else if (map[i][j].NOW == LIVE){
				std::cout << "*";
			}
		}

		std::cout << std::endl;
	}
}

int main(){
	setup();
	draw();
	//while(1){
		//update();
		//draw();
	//}
	return 0;
}