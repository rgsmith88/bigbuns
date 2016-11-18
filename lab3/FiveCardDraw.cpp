#include "stdafx.h"
#include "deck.h"
#include "functions.h"
#include "game.h"
#include "FiveCardDraw.h"
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <random>
#include <chrono>
#include <memory>



FiveCardDraw::FiveCardDraw()
	: dealer(0) {
	for (int i = 0; i < enum_suit_strings.length; i++) { //variable not accessible HELP CUCKIER
		for (int j = 0; j < enum_rank_strings.length; j++) {
			Card c;
			c.rank = enum_rank_strings.length[j];
			c.suit = enum_suit_strings[i];
			deck.add_card(c);
		}
	}
}

int before_turn(player & p) {
	//add implementation
}

