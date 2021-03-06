#ifndef classes_h
#define classes_h
#include "stdafx.h"
#include "functions.h"
#include "hand.h"
#include <string>
#include <vector>

using namespace std;

class Hand;

class Deck {
	public:
		Deck(char * filename);
		// Can use virtual destructor because there is no special destructing that needs to be done here
		int load(char * filename);
		int shuffle();
		int size() const;
		friend void operator<< (Hand& hand, Deck& deck);
		friend ostream& operator<< (ostream& o, const Deck& deck);
	private:
		vector<Card> deck_vector;
};

ostream& operator<< (ostream& o, const Deck& deck);
void operator<< (Hand& hand, Deck& deck); //void because doesn't need to return anything

#endif;