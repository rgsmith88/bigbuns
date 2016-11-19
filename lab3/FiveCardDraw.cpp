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
	: dealer(0){
	for (int i = 2; i <= 14; i++) { //variable not accessible HELP CUCKIER
		for (int j = 0; j < 4; j++) {
			Deck d;
			card_rank c_rank = getRank(i);
			card_suit c_suit = getSuit(j);
			Card c = Card(c_suit, c_rank);
			d.add_card(c);
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
			discardDeck.add_card(toDiscard);
			p.hand.remove_card(stoi(discard));
			cardsToDiscard--;
		}
		catch (int e) {
			switch (e) {
			case out_of_bounds:
				std::cout << "out of bounds!" << std::endl;
				break;
			default:
				std::cout << "try again" << std::endl;
			}

		}

		catch (...) {
			cout << "try again" << endl;
		}
	}
	
}

