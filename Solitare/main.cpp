#include <iostream>
#include "System.h"

int main(){
	
	Main.run();
	/*
	console.setPos(0,12);
	std::cout << "012" << std::endl;
	int num;
	std::cin >> num;
	//std::cout << console.getCursorX() << console.getCursorY() << std::endl;
	std::cout << console.getCursorXNow() << "," << console.getCursorYNow() << std::endl;
	*/
	
	/*
	CARD k;
	k._color = RED;
	k._order = KING;
	k._side = FACE;
	k._suit = DIAMOND;

	CARD d;
	d._color = WHITE;
	d._side = FACE;
	d._order = EIGHT;
	d._suit = SPADE;
	
	CARD a;
	a._color = RED;
	a._side = FACE;
	a._order = SEVEN;
	a._suit = DIAMOND;
	
	CARD b;
	b._color = WHITE;
	b._side = FACE;
	b._order = SIX;
	b._suit = CLUB;

	CARD c;
	c._color = RED;
	c._side = FACE;
	c._order = FIVE;
	c._suit = HEART;
	
	//7 6 5
	col[0].pushACard(d);
	col[0].pushACard(a);
	col[0].pushACard(b);
	col[0].pushACard(c);
	col[0].pushACard(k);

	pCS bot = col[0].getFirst();
	col[0].setFaceUpCard(bot);
	
	while (bot != NULL){
		console.setColor(bot->aCard._color);
		Main.printCardBy(bot->aCard._order);
		Main.printCardBy(bot->aCard._suit);
		std::cout << " ";
		bot = bot->next;
	}
	std::cout << std::endl;
	pCS t = col[0].popTop();
	col[1].pushOn(t);

	std::cout << col[1].size();
	pCS p = col[1].getFirst();
	if (p == NULL){
		std::cout << "NULLL";
	}
	else{
		std::cout << "NOT OK";
	}

	*/
	return 0;
}