#pragma once
#include <ctime>
#include "macro.h"

//a card structure
typedef struct card{
	SUIT _suit;
	COLOR _color;
	ORDER _order;
	SIDE _side;
}CARD;

//a stack structure
typedef struct cardStack{
	CARD aCard;
	struct cardStack* prev;
	struct cardStack* next;
	cardStack():prev(NULL), next(NULL){}
}CS;
typedef struct cardStack* pCS;

CARD *cards = new CARD[NUMBER_OF_CARD];				//the deck holder

//initialize + randomize the card
void init(){
		//i -- counter of the cards
		//j -- the ORDER counter + switch
		//k -- the SUIT counter + switch
		//l -- the COLOR counter
		int j = 0;
		int k = 0;
		for (int i = 0; i < NUMBER_OF_CARD; ++i){
			//the deck is initialized 13 number once
			if (i > 0 && i%ORDER_TOTAL==0){
				//reset j, k
				j = 0;
				k++;
			}

			//color
			if (k == SPADE || k == CLUB){
				cards[i]._color = WHITE;
			}
			else cards[i]._color = RED;
			cards[i]._order = (ORDER)j;			//order of the card
			cards[i]._side = BACK;					//face down all the card
			cards[i]._suit = (SUIT)k;
			j++;
		}
	}

//using knuth shuffling algorithm
void shuffle(){
	srand(time(NULL));
	int i, j;
	for (i = NUMBER_OF_CARD-1; i >=1; --i){
		j = rand()%i;
		CARD temp = cards[j];
		cards[j] = cards[i];
		cards[i] = temp;
	}
}

//Deck class
//array-based stack
typedef class Deck{
private:
	pCS bottom;
	pCS topmost;
	pCS pu3;
	pCS pd3;
	int sz;						//size
	bool threeOut;

public:
	Deck():sz(NUMBER_OF_CARD), bottom(NULL), topmost(NULL), pu3(NULL), pd3(NULL){
		initialize();
		threeOut = false;
	}
	void initialize(){
		init();	//call function init of the card
	}

	void toShuffle(){
		shuffle();	//card shuffle
		bottom = new CS;
		topmost = bottom;
		topmost->aCard = cards[0];
		//copy data over to the stack
		for (int i = 1; i < sz; ++i){
			topmost->next = new CS;
			topmost->next->aCard = cards[i];
			topmost->next->prev = topmost;
			topmost = topmost->next;
		}

		//delete all the card
		delete[] cards;
	}
	
	CARD iTop(){
		return pd3->aCard;
	}

	CARD popiTop(){
		CARD t = pd3->aCard;
		pCS temp = pd3;
		if (pd3 == topmost){
			topmost = topmost->prev;
		}
		else if (pd3 == bottom){
			bottom = bottom->next;
		}
		else{
			if (pd3->prev != NULL)
				pd3->prev->next = pd3->next;	//link to the next card
			if (pd3->next != NULL)
				pd3->next->prev = pd3->prev;	//next card link to the before delete card
		}

		if (pd3 == pu3){
			pd3 = pd3->prev;
		}
		else{
			pd3 = pd3->prev;
			delete temp;
			temp = NULL;
		}
		return t;
	}
	
	CARD popTopCard(){
		CARD t = topmost->aCard;
		pCS temp = topmost;
		topmost->prev->next = topmost->next;
		topmost = topmost->prev;
		delete temp;
		temp = NULL;
		return t;
	}
	
	pCS down3(){
		return pd3;
	}

	pCS up3(){
		return pu3;
	}
	
	//Find the length between up down 3 pointer
	int gap(){
		//signify the end of the deck -->wrap around
		if (pd3 == pu3 && pd3 ==NULL){
			return 0;
		}
		int len = 0;
		pCS t = pd3;
		while (t != pu3){
			//down3 just passed up3
			//This is where all three cards are popped
			//-->needs to draw the next three cards
			if (pu3 != NULL){
				if(pu3->prev == pd3){
					threeOut = true;		//flag that it is the three out pop
					pCS temp = pu3;
					pu3 = pu3->prev;
					delete temp;
					temp = NULL;
					len = -1;
					break;
				}
			}
			len++;
			t= t->prev;
		}
		
		//reaching the end
		if (pu3 == NULL && pd3 != NULL)
			len--;
		return len+1;
	}
	
	CARD top(){
		return topmost->aCard;
	}

	void prevThree(){
		//for checking first time
		if (pu3 == NULL && pd3 == NULL){
			pu3 = pd3 = topmost;
			for (int i = 0; i < 2; ++i){
				if (pu3 != NULL)
					pu3 = pu3->prev;
			}
		}

		else{
			//popped all three cards out
			//pu3 = pd3
			if (pd3 == pu3 && pd3 != NULL){
				if (threeOut == false){
					if (pu3 != NULL){
						pu3 = pu3->prev;
						pd3 = pu3;
					}
				}
				else{
					threeOut = false;
				}
				for (int i = 0; i < 2; ++i){
					if (pu3 != NULL)
						pu3 = pu3->prev;
				}
			}

			else if (pd3 != pu3){
				if (pu3 != NULL)
					pu3 = pu3->prev;
				pd3 = pu3;
				if (pd3 != NULL){
					for (int i = 0; i < 2; ++i){
						if (pu3!= NULL){
							pu3 = pu3->prev;
						}
					}
				}
			}
		}
	}
	
	pCS getTop(){
		return topmost;
	}
	int size(){
		return sz;
	}
	
	bool empty(){
		return sz==0;
	}

	~Deck(){
		//to delete
	}
}DECK;

//naive approach
//make 2 class, column and home

//Home stack class
//can only push
//Sorry no pop
typedef class Home{
private:
	pCS bottom;
	pCS top;
	int sz;
public:
	Home():sz(0),bottom(NULL),top(NULL){}

	void pushACard(CARD aCard){
		if (empty()){
			bottom = new CS;
			bottom->aCard = aCard;
			top = bottom;
			sz++;
		}
		else{
			top->next = new CS;
			top->next->aCard = aCard;
			top->next->prev = top;
			top = top->next;
			sz++;
		}
	}

	bool empty(){
		return sz == 0;
	}

	int size(){
		return sz;
	}
	
	CARD topCard(){
		return top->aCard;
	}

	CARD popTopCard(){
		CARD t = top->aCard;
		pCS temp = top;
		if (top != bottom){
			top->prev->next = top->next;
			top = top->prev;
			top->aCard._side = FACE;
		}

		delete temp;
		sz--;
		return t;
	}

}HOME;

//Column class
typedef class Column{
private:
	pCS bottom;		//the very end of the stack
	pCS top;			//top
	pCS bottomUp;	//the last card that is face up
	int sz;			//size
public:
	Column():sz(0){
		top = bottom = bottomUp = NULL;
	}

	void pushACard(CARD aCard){
		if (empty()){
			bottom = new CS;
			bottom->aCard = aCard;
			top = bottom;
			sz++;
		}
		else{
			top->next = new CS;
			top->next->aCard = aCard;
			top->next->prev = top;
			top = top->next;
			sz++;
		}
	}
	
	void pushOn(pCS &aCS){
		if (empty()){
			bottom = aCS;
			bottomUp = bottom;
			top = bottom;
			sz++;
			//loop to get top card
			while (top->next != NULL){
				sz++;
				top = top->next;
			}
		}
		else{
			top->next = aCS;
			aCS->prev = top;
			while (top->next != NULL){
				sz++;
				top = top->next;
			}

		}
	}

	//decision can only be made when user select:
	//--the top card OR
	//--the last face up card
	pCS popTop(){
		pCS temp = top;
		//update previous card:
		//-Face up
		//-top = prev card
		//only 1 card
		if (top != bottom){
			top->prev->aCard._side = FACE;
			top->prev->next = top->next;
		}
		if (top == bottomUp)
			bottomUp = top->prev;
		top = top->prev;

		temp->prev = NULL;
		sz--;
		return temp;
	}

	pCS popBottomUp(){
	
		//update previous card:
		//-Face up
		//-bottomup = top = bottomup->prev
		int btt = 0;			//bottomUp to topmost
		pCS temp = bottomUp;
		while (temp != top->next){
			btt++;
			temp = temp->next;
		}

		if (bottomUp != bottom){
			bottomUp->prev->aCard._side = FACE;
			bottomUp->prev->next = top->next;
		}
		//check for bottomup == bottom
		else{
			bottom = bottom->prev;
		}

		top = bottomUp->prev;
		temp = bottomUp;
		bottomUp = bottomUp->prev;
		
		temp->prev = NULL;
		sz -= btt;
		if (sz < 0)
			sz = 0;
		return temp;
	}
	
	CARD popTopCard(){
		CARD t = top->aCard;
		pCS temp = top;
		if (top != bottom){
			if (top == bottomUp)
				bottomUp = top->prev;
			top->prev->next = top->next;
			top = top->prev;
			if (top != NULL)
				top->aCard._side = FACE;
		}
		
		sz--;
		delete temp;
		return t;
	}

	CARD topCard(){
		return top->aCard;
	}
	
	pCS topMost(){
		return top;
	}

	pCS getFirst(){
		return bottom;
	}
	
	pCS lastFaceCard(){
		return bottomUp;
	}

	void setFaceUpCard(pCS &aCS){
		bottomUp = aCS;
	}
	//empty?
	bool empty(){
		return sz==0;
	}

	//length
	int size(){
		return sz;
	}
}COL;

HOME home[NUMBER_OF_HOME];		//4 home stack
COL col[NUMBER_OF_COL];			//7 column
DECK deck;							//deck