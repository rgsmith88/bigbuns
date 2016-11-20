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

using namespace std;

FiveCardDraw::FiveCardDraw()
	: dealer(0)
{
	for (int i = 2; i <= 14; i++) { //variable not accessible HELP CUCKIER
		for (int j = 0; j < 4; j++) {
			card_rank c_rank = getRank(i);
			card_suit c_suit = getSuit(j);
			Card c = Card(c_suit, c_rank);
			(this -> main_deck).add_card(c);
		}
	}
}

int FiveCardDraw::before_turn(Player & p) {
	//add implementation
	int cardsToDiscard = 0;
	cout << "player: " << p.name << "wins: " << p.handsWon << "losses: " << p.handsLost << endl;
	cout <<p.hand << endl;
	bool validResponse = false;
	while (!validResponse) {
		cout << "How many cards would you like to discard?" << endl;
		string input;
		cin >> input;
		if (0 <= stoi(input) && stoi(input)< 5) {
			validResponse= true;
			cardsToDiscard = stoi(input);
		}
		else {
			cout << "enter a number from 0 to 5" << endl;
		}
	}
	
	while (cardsToDiscard > 0) {
		cout << "Which card index would you like to discard?" << endl;
		cout << p.hand << endl;
		string discard;
		cin >> discard;
		try {
			Card toDiscard = p.hand[stoi(discard)];
			discardDeck.push_back(toDiscard);
			p.hand.removeCard(stoi(discard));
			cardsToDiscard--;
		}
		catch ("outOfBounds") {
			cout << "out of bounds!" << endl;
		}
		catch () {
			cout << "try again" << endl;
		}
	}
	
}

int FiveCardDraw::turn(Player& p) {
	int cards_needed = 5 - p.hand.size();
	while (cards_needed > 0) {
		int main_deck_size = (this -> main_deck).size(); //store main deck size
		if (main_deck_size == 0) { //check if main deck is empty
			if((this -> discardDeck).size() == 0) { //check if discard deck is empty
				return not_enough_cards;
			}
			(this -> discardDeck).shuffle(); //shuffle discard deck
			p.hand << (this -> discardDeck); //deal cards from discard deck
		}
		p.hand << (this -> main_deck); //deal cards from main deck
		--cards_needed;
	}
	return success;
}

int FiveCardDraw::after_turn(Player& p) {
	cout << "Player Name: " << p.name << endl;
	cout << p.hand << endl;
	return success;
}

int FiveCardDraw::before_round() {
	(this -> main_deck).shuffle(); //shuffle main deck
	int start = (this -> dealer) + 1;
	int num_players = (this -> players).size();
	if ((this -> dealer) == num_players - 1) {
		start = 0;
	}
	for (int i = 0; i < 5; ++i) {
		for (int j = 0; j < (this -> players).size(); ++j) {
			int position = (start + j) % (this -> players).size();
			Player current_player = (this -> players).at(position);
			current_player.hand << (this -> main_deck);
		}
	}
	for (int j = 0; j < (this -> players).size(); ++j) {
		int position = (start + j) % (this -> players).size();
		Player current_player = (this -> players).at(position);
		this -> before_turn(*current_player);
	}
	return success;
}