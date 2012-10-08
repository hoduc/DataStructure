#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <windows.h>

enum STATE{DEAD, LIVE, ZOMBIE};

struct cell{
	STATE NOW;
	STATE FUTURE;
	cell():NOW(DEAD),FUTURE(ZOMBIE){};
};

cell **map;
int row = 40;
int col = 40;

void setup(){
	std::fstream im;		//input map
	//read in row and column
	im.open("map.txt", std::ios::in);
	
	map = new cell*[row];
	for (int i = 0; i < row; ++i){
		map[i] = new cell[col];
	}
	
	std::string line = "";
	im.seekg(0, std::ios::beg);
	for (int i = 0; i < row; ++i){
		getline(im,line);
		for (int j = 0; j < col ;++j){
			if (j > line.length()){
				map[i][j].NOW = DEAD;
				continue;
			}
			if (line[j] == 'L'){
				map[i][j].NOW = LIVE;
			}
			else if (((line[j] == 'D') || (line[j] == ' '))){
				map[i][j].NOW = DEAD;
			}
		}
	}
	
}

void populate(){
	int neighbor_counter;
	for (int i = 0; i < row; ++i){
		for (int j = 0; j < col; ++j){
			neighbor_counter = 0;
			//top-left
			if (((i-1) >= 0) && ((j-1) >= 0)){
				if (map[i-1][j-1].NOW == LIVE)
					neighbor_counter++;
			}
			//top-mid
			if (((i-1) >= 0) && (j >= 0)){
				if (map[i-1][j].NOW == LIVE)
					neighbor_counter++;
			}
			//top-right
			if (((i-1) >= 0) && ((j+1) < col)){
				if (map[i-1][j+1].NOW == LIVE)
					neighbor_counter++;
			}
			//left
			if ((i >= 0) && ((j-1) >= 0)){
				if (map[i][j-1].NOW == LIVE)
					neighbor_counter++;
			}
			//right
			if ((i >= 0) && (j+1) < col){
				if (map[i][j+1].NOW == LIVE)
					neighbor_counter++;
			}
			//low-left
			if (((i+1) < row) && ((j-1) >= 0)){
				if (map[i+1][j-1].NOW == LIVE)
					neighbor_counter++;
			}
			//low-mid
			if (((i+1) < row) && (j >= 0)){
				if (map[i+1][j].NOW == LIVE)
					neighbor_counter++;
			}
			//low-right
			if (((i+1) < row) && ((j+1) < col)){
				if (map[i+1][j+1].NOW == LIVE)
					neighbor_counter++;
			}
			//change the now -cell
			
			//is current cell dead or alive
			if (map[i][j].NOW == LIVE){
				//DEAD b/c of under-population
				if (neighbor_counter < 2)
					map[i][j].FUTURE = DEAD;
				//STILL LIVES
				else if (neighbor_counter >=2 && neighbor_counter <= 3)
					map[i][j].FUTURE = LIVE;
				//DEAD b/c of over-crowdin
				else if (neighbor_counter > 3)
					map[i][j].FUTURE = DEAD;
			}
			else{
				//DEAD->LIVE b/c of reproduction
				if (neighbor_counter == 3)
					map[i][j].FUTURE = LIVE;
			}

		}
	}

	//populate
	for (int i = 0; i < row; ++i){
		for (int j = 0; j < col; ++j){
			map[i][j].NOW = map[i][j].FUTURE;
			map[i][j].FUTURE = ZOMBIE;
		}
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
	//std::cout << "---------------------" << std::endl;
}

int main(){
	setup();
	draw();
	
	while(1){
		Sleep(1000);
		system("cls");
		populate();
		draw();
		
	}
	return 0;
}