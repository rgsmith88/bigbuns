#include "stdafx.h"
#include "functions.h"
#include "deck.h"
#include "hand.h"
#include "player.h"
#include "game.h"
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>

class FiveCardDraw : public Game {
protected:
	size_t dealer; //start at 0
	Deck discardDeck; //under the assumption that the deck constructor initializes empty deck
public:
	FiveCardDraw();
	virtual int before_turn (Player& player);
	virtual int turn(Player& player);
	virtual int after_turn(Player& player);
	virtual int before_round();
	virtual int round();
	virtual int after_round();
};