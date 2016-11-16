#ifndef functions_H
#define functions_H

#include <string>
#include <vector>

using namespace std;

enum card_suit { clubs, diamonds, hearts, spades, invalidSuit };

extern const char* enum_suit_strings[];

extern const int enum_suit_ints[];

enum card_rank { two, three, four, five, six, seven, eight, nine, ten, jack, queen, king, ace, invalidRank };

extern const char* enum_rank_strings[];

extern const int enum_rank_ints[];

struct Card {
	Card(card_suit s, card_rank r);
	bool operator<  (const Card &) const;
	card_suit suit;
	card_rank rank;
};

enum outcome {
	success = 0,
	file_open_error = 1,
	none_well_formed = 2,
	print_error = 3,
	usage_error = 4,
	no_arguments = 5,
	just_shuffle = 6,
	need_shuffle = 7,
	too_many_arguments = 8
};

Card parseString(string card_string);

int parseCardFile(vector<Card> &cards, char * filename);

char* handRank(const vector<Card> & hand);

int printHand(const vector<Card> & cards);

int printCards(const vector<Card> & cards);

int usageMessage(const char* programName, const char * usageMessage);

#endif