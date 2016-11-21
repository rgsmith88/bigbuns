#include "stdafx.h"
#include "deck.h"
#include "functions.h"
#include "hand.h"
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
			(this->main_deck).add_card(c);
		}
	}
}

int FiveCardDraw::before_turn(Player & p) {
	//add implementation
	int cardsToDiscard = 0;
	cout << "player: " << p.name << "wins: " << p.handsWon << "losses: " << p.handsLost << endl;
	cout << p.hand << endl;
	bool validResponse = false;
	while (!validResponse) {
		cout << "How many cards would you like to discard?" << endl;
		string input;
		cin >> input;
		if (0 <= stoi(input) && stoi(input)< 5) {
			validResponse = true;
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
			case erase_out_of_bounds:
				std::cout << "tried erasing out of bounds!" << std::endl;
				break;
			case access_out_of_bounds:
				std::cout << "tried accessing out of bounds!" << std::endl;
				break;
			default:
				std::cout << "try again" << std::endl;
			}

		}

		catch (...) {
			cout << "try again" << endl;
		}
	}
	return success;
}

int FiveCardDraw::turn(Player& p) {
	int cards_needed = 5 - p.hand.size();
	while (cards_needed > 0) {
		int main_deck_size = (this->main_deck).size(); //store main deck size
		if (main_deck_size == 0) { //check if main deck is empty
			if ((this->discardDeck).size() == 0) { //check if discard deck is empty
				return not_enough_cards;
			}
			(this->discardDeck).shuffle(); //shuffle discard deck
			p.hand << (this->discardDeck); //deal cards from discard deck
		}
		p.hand << (this->main_deck); //deal cards from main deck
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
	(this->main_deck).shuffle(); //shuffle main deck
	int start = (this->dealer) + 1;
	int num_players = (this->players).size();
	if ((this->dealer) == num_players - 1) {
		start = 0;
	}
	for (int i = 0; i < 5; ++i) {
		for (size_t j = 0; j < (this->players).size(); ++j) {
			int position = (start + j) % (this->players).size();
			Player current_player = *(this->players).at(position);
			current_player.hand << (this->main_deck);
		}
	}
	for (size_t j = 0; j < (this->players).size(); ++j) {
		int position = (start + j) % (this->players).size();
		Player current_player = *(this->players).at(position);
		this->before_turn(current_player);
	}
	return success;
}

int FiveCardDraw::round() {
	int start = (this->dealer) + 1;
	int num_players = (this->players).size();
	if ((this->dealer) == num_players - 1) {
		start = 0;
	}
	for (size_t j = 0; j < (this->players).size(); ++j) {
		int position = (start + j) % (this->players).size();
		Player current_player = *(this->players).at(position);
		int turn_result = this->turn(current_player);
		if (turn_result != success) {
			return turn_result;
		}
		int after_turn_result = this->after_turn(current_player);
	}
	return success;
}

bool compareHand(std::shared_ptr<Player> p1, std::shared_ptr<Player> p2) {
	if (!p1) {
		return false;
	}
	if (!p2) {
		return true;
	}
	return poker_rank(p1->hand, p2->hand);
}

bool players_same_hands(shared_ptr<Player> p1, shared_ptr<Player> p2) {
	if (!p1) {
		return false;
	}
	if (!p2) {
		return true;
	}
	return equivalent_hands(p1->hand, p2->hand);
}

int FiveCardDraw::after_round() {

	std::vector<std::shared_ptr<Player>> temp_players(players);

	std::sort(temp_players.begin(), temp_players.end(), compareHand);

	vector<int> winners;
	winners.push_back(0);
	for (size_t current_check = 1; current_check < temp_players.size(); ++current_check) {
		shared_ptr<Player> player1 = temp_players.at(0);
		shared_ptr<Player> player_check = temp_players.at(current_check);
		if (players_same_hands(player1, player_check)) {
			winners.push_back(current_check);
		}
	}

	for (size_t i = 0; i < temp_players.size(); i++) {
		if (find(winners.begin(), winners.end(), i) != winners.end()) {
			++(temp_players.at(i)->handsWon);
		}
		else {
			++(temp_players.at(i)->handsLost);
		}
		cout << temp_players.at(i)->name << endl;
		cout << temp_players.at(i)->handsWon << " hands won " << endl;
		cout << temp_players.at(i)->handsLost << " hands lost " << endl;
		cout << "current hand" << endl;
		cout << temp_players.at(i)->hand << endl;
	}

	for (size_t i = 0; i < temp_players.size(); ++i) {
		Player current_player = *temp_players.at(i);
		for (int j = 0; j < current_player.hand.size(); ++j) {
			Card toMove = current_player.hand[j];
			(this->main_deck).add_card(toMove);
			current_player.hand.remove_card(j);
		}

	}

	main_deck.getCardsFromDeck(discardDeck);
}