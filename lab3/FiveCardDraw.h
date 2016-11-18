#pragma once
//#include "Game.h"
#pragma once
#pragma once
#include "stdafx.h"
#include "functions.h"
#include "deck.h"
#include "hand.h"
#include "player.h"
#include "Game.h"
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>

class FiveCardDraw: public Game {
public:

	FiveCardDraw();
		

private:
	size_t dealer; //start at 0
	Deck discardDeck; //under the assumption that the deck constructor initializes empty deck
	int before_turn(player & p); //should be virtual

};
