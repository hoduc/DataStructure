#include <iostream>
#include "Card.h"

int main(){
	//testing card
	CARD king;
	king._order	= KING;
	king._side	= BACK;
	king._suit	= SPADE;
	
	std::cout << king._order << " "		//13
				 << king._side  << " "		//0
				 << king._suit	 << " "		//0
				 ;
	if (king._suit == SUIT::SPADE && king._suit == COLOR::BLACK){
		std::cout << "K" << "S" << std::endl;
	}
	else std::cout << "Wrong";

	return 0;
}