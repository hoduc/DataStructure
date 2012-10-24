#include <ctime>
typedef enum{RED, BLACK, COLOR_TOTAL} COLOR;																 //color of a card
typedef enum{FACE, BACK, SIDE_TOTAL} SIDE;																	//side of a card
typedef enum{SPADE, HEART, DIAMOND, CLUB, SUIT_TOTAL} SUIT;		//suit
typedef enum{ARCH,TWO, THREE, FOUR, FIVE, SIX, SEVEN,
			EIGHT, NINE, TEN, JACK, QUEEN, KING, ORDER_TOTAL} ORDER;							//order of the card

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
	   case TWO: std::cout << "2";
					  break;
		case THREE: std::cout << "3";
						break;
		case FOUR: std::cout << "4";
					  break;
		case FIVE: std::cout << "5";
					  break;
		case SIX: std::cout << "6";
					  break;
		case SEVEN: std::cout << "7";
					  break;
		case EIGHT: std::cout << "8";
					  break;
	   case NINE: std::cout << "9";
					  break;
	   case TEN: std::cout << "10";
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
		case SPADE : std::cout << "S";
						 break;
		case HEART : std::cout << "H";
						 break;
		case DIAMOND : std::cout << "D";
						   break;
		case CLUB : std::cout << "C";
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

//52 card total
#define NUMBER_OF_CARD 52

//Deck class
typedef class Deck{
private:
	CARD *cards;
	pCS _deck;
	pCS top;
	int sz;

public:
	Deck():sz(NUMBER_OF_CARD){
		cards = new CARD[NUMBER_OF_CARD];
		_deck = new CS;
		top = _deck;
		init();
	}
	
	void init(){
		//i -- counter of the cards
		//j -- the ORDER counter + switch
		//k -- the SUIT counter + switch
		//l -- the COLOR counter
		int j = 0;
		int k = 0;
		for (int i = 0; i < sz; ++i){
			//the deck is initialized 13 number once
			if (i > 0 && i%ORDER_TOTAL==0){
				//reset j, k
				j = 0;
				k++;
			}

			//color
			if (k == SPADE || k == CLUB){
				cards[i]._color = BLACK;
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
		for (i = sz-1; i >=1; --i){
			j = rand()%i;
			CARD temp = cards[j];
			cards[j] = cards[i];
			cards[i] = temp;
		}

		//copy to the main linked list structure
		for (int i = 0; i < NUMBER_OF_CARD; ++i){
			top->aCard = cards[i];
			top->next = new CS;
			top->next->prev = top;
			top = top->next;
		}

		top = top->prev;
	}
	
	int size(){
		return sz;
	}
	
	bool empty(){
		return sz==0;
	}
	
	pCS pop(){
		pCS temp = top;
		top->prev->next = top->next;
		top = top->prev;
		return temp;
	}

	void print(){
		pCS temp = _deck;
		int i = 0;
		while (temp != top->next){
			if (i %ORDER_TOTAL == 0)
				std::cout << std::endl;
			printCardBy(temp->aCard._order);
			printCardBy(temp->aCard._suit);
			printCardBy(temp->aCard._color);
			printCardBy(temp->aCard._side);
			std::cout << " ";
			temp = temp->next;
			i++;
		}
	}
}DECK;

//Mini Stack class -- used for Home stack
//						 -- used for Column
//Doubly linked list implementation
DECK deck;