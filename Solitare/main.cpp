#include <iostream>
#include "Card.h"

int main(){
	/*
	//testing card
	CARD king;
	king._order	= KING;
	king._side	= BACK;
	king._suit	= SPADE;
	
	std::cout << king._order << " "		//13
				 << king._side  << " "		//0
				 << king._suit	 << " "		//0
				 ;
	if (king._suit == SPADE && king._suit == BLACK){
		std::cout << "K" << "S" << std::endl;
	}
	else std::cout << "Wrong";
	
	*/


	//testing deck init
	deck.print();		//print the deck
	std::cout << std::endl;

	//testing shuffle
	std::cout << "TESTING SHUFFLE" << std::endl;
	deck.shuffle();
	deck.print();
	std::cout << std::endl;
	
	//testing pop
	std::cout << "Testing pop" << std::endl;
	CARD t = deck.pop();
	printCardBy(t._order);
	std::cout << "-";
	printCardBy(t._suit);
	std::cout << "-";
	printCardBy(t._side);
	std::cout << "-";
	printCardBy(t._color);
	std::cout << std::endl;
	return 0;
}