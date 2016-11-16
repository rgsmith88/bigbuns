#include "stdafx.h"
#include "deck.h"
#include "functions.h"
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <random>
#include <chrono>

using namespace std;

Deck::Deck(char * filename)
	: deck_vector()
{
	int load_status = load(filename);
	if (load_status != success) {
		cout << "File could not be opened" << endl;
		throw load_status;
	}
}

//virtual ~Deck(); //DO I NEED TO PUT COMMENT HERE??

int Deck::load(char * filename) {
	ifstream in(filename);
	if (in.is_open()) {
		string localLine;
		while (getline(in, localLine)) {
			istringstream iss(localLine);
			bool empty = true; //kees track of empty lines, allowowing program to skip lines without printing out "too many" or "too few"
			string cardString;
			while (iss >> cardString) {
				if (cardString.length() == 2 || cardString.length() == 3) { //make sure string is right length
					empty = false; //
					Card card = parseString(cardString);
					if (card.suit != invalidSuit && card.rank != invalidRank) { //make sure ranks are between 2-Ace and suits one of the four
						deck_vector.push_back(card); //push back string to temporary vector hand
					}
					else { cout << "String not well-formed" << endl; }
				}
				else { cout << "String not well-formed" << endl; }
			}
		}
		return success;
	}
	return file_open_error;
}

int Deck::shuffle() {
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::shuffle(deck_vector.begin(), deck_vector.end(), std::default_random_engine(seed));
	return success;
}

int Deck::size() const {
	return deck_vector.size();
}

ostream& operator<< (ostream& o, const Deck& deck) {
	for (Card c : deck.deck_vector) {
		//use enum_rank_strings so that enum text is printed instead of enum numbers
		o << enum_rank_strings[c.rank] << " of " << enum_suit_strings[c.suit] << endl;
	}
	return o;
}