typedef enum{RED, BLACK} COLOR;																 //color of a card
typedef enum{FACE, BACK} SIDE;																	//side of a card
typedef enum{SPADE = BLACK, HEART = RED, DIAMOND = RED, CLUB = BLACK} SUIT;		//suit
typedef enum{ARCH, ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN,
			EIGHT, NINE, TEN, JACK, QUEEN, KING} ORDER;							//order of the card

//a card structure
typedef struct card{
	SUIT _suit;
	ORDER _order;
	SIDE _side;
}CARD;

//Deck class

//Column class (Link list of card)

//Column class (7 column)

//Home class (stack of card - 4)

