#pragma once
#include "macro.h"
#include "Card.h"
#include "Console.h"
#include <string>
#include <iomanip>

typedef class System{
private:
public:
	System(){}

	//shuffle the deck
	void init(){
		deck.toShuffle();
		setUpCol();
	}

	void run(){
		init();
		int choice;
		bool isWin = win();
		bool endMove = noMove();
		while(isWin == false && endMove == false){
			printLayout();
			std::cout << "Make a choice : ";
			std::cin >> choice;
			execute(choice);
			system("cls");
			isWin = win();
			endMove = noMove();
		}

		if (isWin == true || endMove == true){
			system("cls");
			console.setPos(console.getConsoleWidth()/2, console.getConsoleHeight()/2);
			std::string youLose = "YOU LOSE!!!";
			std::string youWin =  "YOU WIN!!!!";
			
			int end = 0;
			if (endMove){
				end = youLose.length();
			}
			else if (isWin){
				end = youWin.length();
			}

			for (int i = 0; i < end; ++i){
				if (endMove){
					std::cout << youLose[i];
				}
				else if (isWin){
					std::cout << youWin[i];
				}
				Sleep(500);
			}

			for (int i = 0; i < 5; ++i){
				std::cout << ".";
				Sleep(500);
			}
		}

	}
	
	void execute(int n){
		switch(n){
			case 1: prevThree();
					  break;
			case 2: deckToHome();
					  break;
			case 3: deckToCol();
					  break;
			case 4: homeToCol();
					  break;
			case 5: colToHome();
				     break;
			case 6: colToCol();
					  break;
			default:	std::cout <<"Dude!Are you nut!!!" << std::endl;
						//clear the stdinput
						std::cin.clear();
						std::cin.ignore(INT_MAX, '\n');
					  break;
		}
	}

	//check for win or lose
	bool win(){
		//the homestack is filled with 13 cards each
		if		((home[0].size() == NUMBER_OF_CARD/4)
			    && (home[0].size() == home[1].size())
				 && (home[1].size() == home[2].size())
				 && (home[2].size() == home[3].size())){
			return true;
		}
		return false;
	}

	//checking for no move
	bool noMove(){
		int step = 0;	//for counting if there is a move or not
		
		pCS temp = deck.getTop();
		
		//Is there any move from:
		//DECK --> home
		//DECK --> column
		while (temp != NULL){
			//Is there a move from deck to home
			//Find home
			int hi = findHomeBy(temp->aCard._suit);
			if (home[hi].empty()){
				//if the top card is arch --> still move
				if (temp->aCard._order == ARCH){
					return false;
				}
			}
			else{
				if ((temp->aCard._order == home[hi].topCard()._order+1)
				 &&(temp->aCard._color == home[hi].topCard()._color)){
					return false;
				}
			}
			
			//is there a move from deck to column
			for (int i = 0; i < NUMBER_OF_COL; ++i){
				if (col[i].empty()){
					if (temp->aCard._order == KING){
						return false;
					}
				}
				else{
					if ((temp->aCard._order == col[i].topCard()._order-1)
						&& (temp->aCard._color != col[i].topCard()._color)){
						return false;
					}
				}
			}
			//next three card
			for (int i = 0; i < 2 ; ++i, temp = temp->prev){
				if (temp == NULL)
					break;
			}
			if (temp == NULL)
				break;
		}
		
		//Is there any move from column to column
		for (int i = 0; i < NUMBER_OF_COL; ++i){
			for (int j = i+1; j < NUMBER_OF_COL; ++j){
				//Is there a move from a column to other column
				if (((col[i].topCard()._order+1 == col[j].topCard()._order)
				|| (col[i].topCard()._order-1 == col[j].topCard()._order))
				&& (col[i].topCard()._color != col[j].topCard()._color)){
					return false;
				}

				if (((col[i].lastFaceCard()->aCard._order+1 == col[j].topCard()._order)
				|| (col[i].lastFaceCard()->aCard._order-1 == col[j].topCard()._order))
				&& (col[i].lastFaceCard()->aCard._color != col[j].topCard()._color)){
					return false;
				}
			}
		}
		return true;

	}
	
	void prevThree(){
		deck.prevThree();
	}
	
	//Push cards to each column by the following order
	//COL[i] = (i+1) cards
	void setUpCol(){
		for (int i = 0; i < NUMBER_OF_COL; ++i){
			for (int j = 0; j < (i+1); ++j){
				col[i].pushACard(deck.popTopCard());
			}
			col[i].topMost()->aCard._side = FACE;
			pCS temp = col[i].topMost();
			col[i].setFaceUpCard(temp);
		}
	}

	//Moving top card from deck to home
	void deckToHome(){
		if (deck.gap() != 0){
			//push card to empty box of the 4s
			int hi = findHomeBy(deck.iTop()._suit);
			if (home[hi].empty()){
				if (deck.iTop()._order != ARCH){
					std::cout << "Has to be arch!!!DUDE!!!!" << std::endl;
				}
				//it is ARCH
				else{
					//do not care about the color, just push
					home[hi].pushACard(deck.popiTop());
				}
			}
			//There is already some card in the home
			else{
				//must always push a card with order one bigger than the top card
				//and the same color//
				if ((home[hi].topCard()._order+1 == deck.iTop()._order)
				&& (home[hi].topCard()._color == deck.iTop()._color)){
					home[hi].pushACard(deck.popiTop());
				}

				//some error
				else{
					//Different Color
					if (home[hi].topCard()._color != deck.iTop()._color){
						std::cout << "Not the same color!!!";
					}
					
					//wrong order
					if (home[hi].topCard()._order+1 != deck.iTop()._order){
						std::cout << "Wrong order!!!";
					}
				}
			
			}
		}
		//first time start the game
		//or the 3 cards gap is popped off all
		else{
			std::cout << "Tell the deck to take out 3 cards!!!DUDE";
			std::cout << std::endl;
		}
	}

	//find the homr number by suit
	int findHomeBy(SUIT s){
		//finding the home stack by suit
		for (int i = 0; i < NUMBER_OF_HOME; ++i){
			//the home is not empty and was same suit
			if (!home[i].empty() && home[i].topCard()._suit == s){
				return i;
			}
		}

		//Cannot find any home that is not empty and same suit 
		//meaning all 4 is empty

		for (int i = 0; i < NUMBER_OF_HOME; ++i){
			if (home[i].empty()){
				return i;
			}
		}

		//will it ver get here???
		return -1;

	}
	
	//Moving card from deck to column
	void deckToCol(){
		int icol;
		std::cout << "Which cols?";
		std::cin  >> icol;
		while (icol > NUMBER_OF_COL || icol < 0){
			std::cout << "Which cols?";
		   std::cin >> icol;
		}

		//the column is right
		//Now check the card
		//making sure the deck is not empty

		if (!col[icol].empty()){
			if ((deck.iTop()._color != col[icol].topCard()._color)
			&& (deck.iTop()._order+1 == col[icol].topCard()._order)){
				col[icol].pushACard(deck.popiTop());
				col[icol].topMost()->aCard._side = FACE;
			}
			else{
				if (deck.iTop()._color == col[icol].topCard()._color){
					std::cout << "Need to be alternating color!!!" << std::endl;
				}

				if (deck.iTop()._order+1 != col[icol].topCard()._order){
					std::cout << "Wrong order!!!" << std::endl;
				}
			}	
		}
		//the column is empty
		else{
			//can only push KING
			if (deck.iTop()._order == KING){
				col[icol].pushACard(deck.popiTop());
				col[icol].topMost()->aCard._side = FACE;
			}
			else{
				std::cout << "King comes first!!!" << std::endl;
			}
		}
	}

	//Moving card from HOME --> column
	void homeToCol(){
		//Input the home index to choose from
		int hi;
		std::cout << "Which one?";
		std::cin >> hi;
		//Making sure the number is right
		while (hi > NUMBER_OF_HOME || hi < 0){
			std::cout << "Which one?";
			std::cin >> hi;	
		}

		//Input the col index to choose from
		int icol;
		std::cout << "Which cols?";
		std::cin  >> icol;
		//Making sure the colunm index is legit
		while (icol > NUMBER_OF_COL || icol < 0){
			std::cout << "Which cols?";
		   std::cin >> icol;
		}

		//colunm and home indexes are right
		//checking for the push
		//Condition:
		//home[hi] is not empty
		//alternating cards' color
		//difference is 1 in order
		if ((!home[hi].empty()) 
		&& (home[hi].topCard()._order+1 == col[icol].topCard()._order)
		&& (home[hi].topCard()._color != col[icol].topCard()._color)){
			col[icol].pushACard(home[hi].popTopCard());
		}
		
		//some error
		else{
			//the home[hi] is empty
			if (home[hi].empty())
				std::cout << "HOME stack " << hi << " is empty!!!";
			//the home[hi] is wrong order
			else {
				if (home[hi].topCard()._order+1 != col[icol].topCard()._order)
				std::cout << "Wrong order!!!";
				//same color
				if (home[hi].topCard()._color == col[icol].topCard()._color)
					std::cout << "Has to be alternating color!!!";
				std::cout << std::endl;
			}
		}
			
	}
	
	//Moving card from column to home
	void colToHome(){
		//Input the col index to choose from
		int icol;
		std::cout << "Which cols?";
		std::cin  >> icol;
		//Making sure the colunm index is legit
		while (icol > NUMBER_OF_COL || icol < 0){
			std::cout << "Which cols?";
		   std::cin >> icol;
		}

		//column and index are OK
		//now pushing cards
		//Condition :
		//--col[icol] is not empty
		//--col[icol]'s color and top of home[hi] is differenced
		//--col[icol]'s order is 1 away from home[hi]
		//find home
		int hi = findHomeBy(col[icol].topCard()._suit);
		if (!col[icol].empty()){
			if (!home[hi].empty()){
				if ((col[icol].topCard()._order-1 == home[hi].topCard()._order)
				&& (col[icol].topCard()._color == home[hi].topCard()._color)){
					//pushing card to home
					home[hi].pushACard(col[icol].popTopCard());
				}
				//some error
				else{
						//wrong order
					if (col[icol].topCard()._order-1 != home[hi].topCard()._order)
						std::cout << "Wrong order!!!";
					//same color
					if (col[icol].topCard()._color != home[hi].topCard()._color)
						std::cout << "Same color plzzz!!!";
				}
			}

			//home is empty
			else{
				//only can push arch
				if (col[icol].topCard()._order == ARCH)
					home[hi].pushACard(col[icol].popTopCard());
				else std::cout << "Must be Arch!!!Dude!!!";
			}
		}
		//error
		else{
			if (col[icol].empty()){
				std::cout << "Column " << icol << " is empty!!!"; 
			}

			std::cout << std::endl;
		}


	}
	
	//Moving cards between column
	void colToCol(){
		int his, hid;	//source and destination col index;
		int his_ts;		//source top or series

		//input and bounds check
		std::cout << "Which col? ";
		std::cin >> his;
		while (his < 0 || his > NUMBER_OF_COL){
			std::cout << "Which col?";
			std::cin >> his_ts;
		}
		
		//select last face ups series or last card only
		std::cout << "Select option[0-Top Card, 1-A series]:";
		std::cin  >> his_ts;

		while (his_ts < 0 || his_ts > 1){
			std::cout << "Select option[0-Top Card, 1-A series]:";
			std::cin  >> his_ts;
		}

		std::cout << "To which col? ";
		std::cin >> hid;
		while (hid < 0 || hid > NUMBER_OF_COL){
			std::cout << "To which col?";
			std::cin >> hid;
		}

		//Everything is right
		//the source column and destination is not empty
		if (!col[his].empty()){
			//destination is not empty
			if (!col[hid].empty()){
				//normal push
				if (his_ts == 0){
					//pushing topcard
					if ((col[his].topMost()->aCard._order+1 == col[hid].topMost()->aCard._order)
					&& (col[his].topMost()->aCard._color != col[hid].topMost()->aCard._color)){
						pCS t = col[his].popTop();
						col[hid].pushOn(t);
					}
					else
					{
						if (col[his].topMost()->aCard._order+1 != col[hid].topMost()->aCard._order){
							std::cout << "Wrong order!!!";
						}

						if (col[his].topMost()->aCard._color == col[hid].topMost()->aCard._color){
							std::cout << "Same color!!!";
						}
					}
				}
				
				else if (his_ts == 1){
					//pushing last face up card
					if ((col[his].lastFaceCard()->aCard._order+1 == col[hid].topMost()->aCard._order)
					&& (col[his].lastFaceCard()->aCard._color != col[hid].topMost()->aCard._color)){
						pCS t = col[his].popBottomUp();
						col[hid].pushOn(t);
					}
					else
					{
						if (col[his].lastFaceCard()->aCard._order+1 != col[hid].topMost()->aCard._order){
							std::cout << "Wrong order!!!";
						}

						if (col[his].lastFaceCard()->aCard._color == col[hid].topMost()->aCard._color){
							std::cout << "Same color!!!";
						}
					}
				}
			}

			//destination is empty
			else{
				//Can only push king
				//top card
				if (his_ts == 0){
					if (col[his].topMost()->aCard._order == KING){
						pCS t = col[his].popTop();
						col[hid].pushOn(t);
					}
					else
						std::cout << "King comes first!!!" << std::endl;
				}
				//top most
				else if (his_ts == 1){
					if (col[his].lastFaceCard()->aCard._order == KING){
						pCS t = col[his].popBottomUp();
						col[hid].pushOn(t);
					}
					else
						std::cout << "King comes first!!!" << std::endl;
				}
			}
		}

		else{
			std::cout << "Source column is empty!!!Nothing to do here!!!";
		}
	}

	//printing layout
	void printLayout(){
		printDeck();
		printHome();
		printColumns();
		printMenu();
	}
	
	//print the deck card
	void printDeck(){
		console.setPos(0,0);
		console.setColor(GREEN);
		std::cout << "DECK" << std::endl;
		console.setDefaultColor();
	
		pCS t = deck.down3();
		int len = deck.gap();
		if (len > 0){
			int start_x = 0;
			int start_y = len;
			int i;
			//print the card that is in the gap
			for (i = 0; i < len; ++i){
				console.setPos(start_x, start_y--);
				console.setColor(t->aCard._color);
				printCardBy(t->aCard._order);
				printCardBy(t->aCard._suit);
				std::cout << std::endl;
				t = t->prev;
			}

			//print the card that is already popped[' ']
			while (i < NUMBER_OF_GAP){
				console.setPos(start_x,start_y+len+1);
				std::cout << " " << std::endl;
				i++;
			}

			std::cout << std::endl;

		}
		else{
			//It means either the deck is not shown or 3 cards had been popped
			for (int i = 0; i < NUMBER_OF_GAP; ++i){
				std::cout << " " << std::endl;
			}
		}
		console.setDefaultColor();
	}
	
	//print home stack
	void printHome(){
		console.setPos(console.getConsoleWidth()-50,0);
		console.setColor(PINK);
		std::cout << std::setw(4) << std::left << "H"
					 << std::setw(4) << std::left << "O"
					 << std::setw(4) << std::left << "M"
					 << std::setw(4) << std::left << "E"
					 << std::endl;
		console.setPos(console.getConsoleWidth()-50,1);
		console.setDefaultColor();
		for (int i = 0; i < NUMBER_OF_HOME; ++i){
			if (home[i].empty()){
				std::cout << "--- ";
			}
			else{
				CARD card = home[i].topCard();
				console.setColor(card._color);
				printCardBy(card._order);
				printCardBy(card._suit);
				if (card._order != TEN)
					std::cout << " ";
				console.setDefaultColor();
			}
		}
		console.setDefaultColor();
		std::cout << std::endl;
	}
	
	//print column
	void printColumns(){
		console.setPos(0,5);
		console.setColor(BLUE);
		std::cout << "COLUMNS:";
		console.setDefaultColor();
		int start_y;
		int start_x = 18;
		//print columns number/index
		for (int i = 0; i < NUMBER_OF_COL; ++i){
			start_y = 5;
			if (i > 0)
				console.setPos(start_x+i*4,start_y);
			else console.setPos(start_x, start_y);

			std::cout << std::setw(4) << std::left << i;
		}

		//main printing col methods
		for (int i = 0; i < NUMBER_OF_COL; ++i){
			start_y = 6;
			if (i > 0)
				console.setPos(start_x+i*4,start_y);
			else console.setPos(start_x,start_y);
			if (col[i].empty()){
				std::cout << std::setw(4) << "---" << std::endl;
			}
			else{
				pCS temp = col[i].getFirst();
				while (temp != NULL){
					//face down card
					if (temp->aCard._side == BACK){
						std::cout << std::setw(4) << "***" << std::endl;
						console.setPos(start_x+i*4,++start_y);
					}
					//face up card
					else{
						console.setColor(temp->aCard._color);
						printCardBy(temp->aCard._order);
						printCardBy(temp->aCard._suit);
						std::cout << std::endl;
						console.setPos(start_x+i*4,++start_y);
					}
					temp = temp->next;
				}
			}
			console.setDefaultColor();
		}
	}
	
	//print selection
	void printMenu(){
		console.setPos(0,console.getConsoleHeight()-30);
		std::string dstring = "DECK";
		std::string hstring = "HOME";
		std::string cstring = "COLUMNS";

		//DECK ACTION
		std::cout << "1. ";console.setColor(GREEN);std::cout << dstring;console.setDefaultColor();std::cout << " shows next three cards" << std::endl;
		console.setDefaultColor();
		std::cout << "2. Move cards from ";console.setColor(GREEN);std::cout << dstring;console.setDefaultColor();std::cout << " to ";console.setColor(PINK);std::cout << hstring << std::endl;
		console.setDefaultColor();
		std::cout << "3. Move cards from ";console.setColor(GREEN);std::cout << dstring;console.setDefaultColor();std::cout << " to ";console.setColor(BLUE);std::cout << cstring << std::endl;
		console.setDefaultColor();		
		
		//HOME ACTION
		std::cout << "4. Move cards from ";console.setColor(PINK);std::cout << hstring;console.setDefaultColor();std::cout << " to ";console.setColor(BLUE);std::cout << cstring << std::endl;
		console.setDefaultColor();

		//COLUMN ACTION
		std::cout << "5. Move cards from ";console.setColor(BLUE);std::cout << cstring;console.setDefaultColor();std::cout << " to ";console.setColor(PINK);std::cout << hstring << std::endl;
		console.setDefaultColor();
		std::cout << "6. Move cards from ";console.setColor(BLUE);std::cout << cstring;console.setDefaultColor();std::cout << " to ";console.setColor(BLUE);std::cout << cstring << std::endl;
		console.setDefaultColor();
	}

	void printCardBy(COLOR c){
		switch(c){
			case RED:	std::cout << "R";
						break;
			case BLACK : std::cout << "B";
		}
	}
	
	void printCardBy(ORDER o){
		switch(o){
			case ARCH: std::cout << "A";
					  break;
			case TWO:
			case THREE:
			case FOUR:
			case FIVE:
			case SIX:
			case SEVEN:
			case EIGHT:
			case NINE:
			case TEN:  std::cout << o+1;
						  break;
			case JACK: std::cout << "J";
						  break;
			case QUEEN: std::cout << "Q";
						  break;
			case KING: std::cout << "K";
						  break;
		}
	}

	void printCardBy(SUIT s){
		switch(s){
			case SPADE : std::cout << (char)6;
							 break;
			case HEART : std::cout << (char)3;
							 break;
			case DIAMOND : std::cout << (char)4;
								break;
			case CLUB : std::cout << (char)5;
							break;
		}
	}

	void printCardBy(SIDE s){
		switch(s){
			case FACE : std::cout << "^";
							break;
			case BACK : std::cout << "*";
							break;
		}
	}

	
}SYSTEM;

SYSTEM Main;


