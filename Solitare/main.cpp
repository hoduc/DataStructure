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
	pCS t = deck.pop();
	printCardBy(t->aCard._order);
	printCardBy(t->aCard._suit);
	printCardBy(t->aCard._side);
	printCardBy(t->aCard._color);
	std::cout << std::endl;
	
	//reprint , will miss one card
	deck.print();
	std::cout << std::endl;

	//Testing Home stack
	std::cout << "Testing home" << std::endl;
	HOME SPADE_STACK;
	std::cout << SPADE_STACK.size() << std::endl;// 0
	
	//trying to add a NOT ARCH to the stack
	//1.King SPADE
	pCS KS = new CS;
	KS->aCard._color = BLACK;
	KS->aCard._order = KING;
	KS->aCard._side = FACE;
	KS->aCard._suit = SPADE;

	SPADE_STACK.push(KS);
	std::cout << SPADE_STACK.size() << std::endl;	//0

	//2. ARCH SPADE
	pCS AS = new CS;
	AS->aCard._color = BLACK;
	AS->aCard._order = ARCH;
	AS->aCard._side = FACE;
	AS->aCard._suit = SPADE;

	SPADE_STACK.push(AS);
	std::cout << SPADE_STACK.size() << std::endl;	//1

	//3. QUEEN SPADE
	pCS QS = new CS;
	QS->aCard._color = BLACK;
	QS->aCard._order = QUEEN;
	QS->aCard._side = FACE;
	QS->aCard._suit = SPADE;

	SPADE_STACK.push(QS);
	std::cout << SPADE_STACK.size() << std::endl;	//1
	
	//4. TWO DIAMOND
	pCS TD = new CS;
	TD->aCard._color = RED;
	TD->aCard._order = TWO;
	TD->aCard._side = FACE;
	TD->aCard._suit = DIAMOND;

	SPADE_STACK.push(TD);
	std::cout << SPADE_STACK.size() << std::endl;	//1

	//5. THREE HEART
	pCS T3H = new CS;
	T3H->aCard._color = RED;
	T3H->aCard._order = THREE;
	T3H->aCard._side = FACE;
	T3H->aCard._suit = HEART;

	SPADE_STACK.push(T3H);
	std::cout << SPADE_STACK.size() << std::endl;	//1

	//6.TWO SPADE
	pCS TS = new CS;
	TS->aCard._color = BLACK;
	TS->aCard._order = TWO;
	TS->aCard._side = FACE;
	TS->aCard._suit = SPADE;

	SPADE_STACK.push(TS);
	std::cout << SPADE_STACK.size() << std::endl;	//2

	//print the stack
	SPADE_STACK.print();
	std::cout << std::endl;
	return 0;
}