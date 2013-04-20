#pragma once
//the 8-bit color
enum COLOR{
BLACK = 0,DARKBLUE, DARKGREEN, DARKTEAL, 
DARKRED, DARKPINK, DARKYELLOW, GRAY, 
DARKGRAY, BLUE, GREEN, TEAL, 
RED, PINK, YELLOW, WHITE
};	//asbusing the auto increment side-effect of enum

typedef enum{FACE, BACK, SIDE_TOTAL} SIDE;										//side of a card
typedef enum{HEART, DIAMOND, CLUB, SPADE, SUIT_TOTAL} SUIT;	//suit=corresponding ascii
typedef enum{ARCH,TWO, THREE, FOUR, FIVE, SIX, SEVEN,
			EIGHT, NINE, TEN, JACK, QUEEN, KING, ORDER_TOTAL} ORDER;			//order of the card
//52 card total
#define NUMBER_OF_CARD 52
#define NUMBER_OF_HOME 4
#define NUMBER_OF_COL 7
#define NUMBER_OF_GAP 3		//the gap between card shuffle