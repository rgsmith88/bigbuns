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
	: dealer(0), commonChipPot(0), current_bet(0) //commonChipPot & current_bet are NEW

{
	for (int i = 2; i <= 14; i++) {
		for (int j = 0; j < 4; j++) {
			card_rank c_rank = getRank(i);
			card_suit c_suit = getSuit(j);
			Card c = Card(c_suit, c_rank);
			(this->main_deck).add_card(c);
		}
	}
}

//void whichAction(bool betOnTable ) {
//	cout << "Which action would you like to perform? (" << endl;
//	string input;
//	cin >> input;
//}

//NEW: BETTING PHASE
void FiveCardDraw:: betting_phase(Player &p) {
	bool bet_on_table = false;
	bool validResponse_CB = false;
	bool validResponse_FCR = false;
	bool playerDone = false;

	if (!bet_on_table) { // players may either check or bet 1-2 chips
		while (!validResponse_CB) {
			cout << "Would you like to 'check' or 'bet'?" << endl;
			string CheckOrBet;
			cin >> CheckOrBet;
			if (CheckOrBet == "check") {
				validResponse_CB = true;
				playerDone = true;
			}
			else if (CheckOrBet == "bet") {
				validResponse_CB = true;
				bool validBet = false;
				while (!validBet) {
					cout << "Would you like to bet '1' or '2' chips?" << endl;
					string betAmount;
					cin >> betAmount;
					if (stoi(betAmount) == 1 || stoi(betAmount) == 2) {
						if (stoi(betAmount) == 1) {
							if (p.chips < 1) {
								cout << "less than one chip. You must check and are going to check right now" << endl;
								//validBet == false;
								playerDone = true;
							}
							else {
								validBet == true;
								++commonChipPot;
								++p.chips_bet;
								--p.chips;
								bet_on_table = true;
								++current_bet;
							}

						}
						else { //they waged a bet of 2
							if (p.chips < 2) { //if they have less than 2 chips they cant bet 2 chips so they must either bet one or check
								if (p.chips < 1) { //player doesn't have any chips so they must check
									cout << "less than one chip. You must check and are going to check right now" << endl;
									//validBet == false;
									playerDone = true;
								}
								else { //the player has exactly one chip so we will say invalid bet which will prompt them again to bet or check
									cout << "you only have one chip so you cannot bet 2" << endl;
									validBet = false;
								}
							}
							else { //the player has 2 or more chips so they can bet 2 chips
								validBet = true;
								commonChipPot += 2;
								p.chips_bet += 2;
								p.chips -= 2;
								bet_on_table = true;
								current_bet += 2;
							}
						}
					}

					else { // the user entered a bet amount other than 1 or 2 so its invalid
						cout << "invalid bet amount" << endl;
						validBet = false;
					}

				}

			}
			else {
				cout << "invalid response!" << endl;
				validResponse_CB = false;
			}
		}
	}
	else { //There is a bet placed on the table so the player can either FOLD, CALL, or RAISE
		while (!validResponse_FCR) {

			cout << "Would you like to 'fold' 'call' or 'raise'?" << endl;
			string FoldCallOrRaise;
			cin >> FoldCallOrRaise;
			if (FoldCallOrRaise == "fold") {
				validResponse_FCR = true;
				playerDone = true;
				//commonChipPot += p.chips_bet;
			}
			else if (FoldCallOrRaise == "call") {
				validResponse_FCR = true;
				//check if player has enough money
				if(p.chips < current_bet - p.chips_bet) {
					commonChipPot += p.chips;
					p.chips_bet += p.chips;
					p.chips = 0; //dangerous move here hard coding it to zero my b guys. CHECK ME OUT WHEN DEBUGGING
					std::cout << "You don't have enough money to call, you're going ALL IN" << std::endl;
					playerDone = true;
				}
				else if (p.chips == current_bet - p.chips_bet) { //player has same amount of chips as current bet
					commonChipPot += p.chips;
					p.chips_bet += current_bet;
					p.chips -= current_bet; //this should be zero as they will have bet the last of their chips
				}
				else { //They have more money than current bet
					commonChipPot += current_bet;
					p.chips -= current_bet;
					p.chips_bet += current_bet;

				}
			}
			else if (FoldCallOrRaise == "raise") {
				if (p.chips <= current_bet - p.chips_bet) { //If the player doesnt have more than the current bet they cannot raise
					cout << "Sorry you actually dont have enough chips to raise--fold or call" << endl;
					validResponse_FCR = false;
				}
				else {
					validResponse_FCR = true;
					if (p.chips == current_bet - p.chips_bet - 1) { //in this case the player can only raise by one
						cout << "You can only raise by 1 chip...raising by one chip" << endl;
						commonChipPot += 1;
						--p.chips;
						p.chips_bet += 1;
					}

					else {
						cout << "how many chips would you like to raise? '1' or '2'?" << endl;
						string raiseAmount;
						cin >> raiseAmount;
						if (stoi(raiseAmount) == 1 || stoi(raiseAmount) == 2) {
							validResponse_FCR = true;
							if (stoi(raiseAmount) == 1) {
								commonChipPot += 1;
								--p.chips;
								p.chips_bet += 1;
							}
							else if (stoi(raiseAmount) == 2) {
								commonChipPot += 2;
								p.chips-=2;
								p.chips_bet += 2;
							}
							else {
								cout << "invalid response. Raise by a value of '1' or '2'" << endl;
								validResponse_FCR = false;
							}
						}
					}

				}
			}
			else {
				cout << "ivalid response" << endl;
				validResponse_FCR = false;
			}
		}



	}
}

int FiveCardDraw::before_turn(Player & p) {
	int cardsToDiscard = 0;
	cout << endl;
	cout << p << endl;
	cout << p.hand;
	bool validResponse = false;
	while (!validResponse) {
		cout << "How many cards would you like to discard?" << endl;
		string input;
		cin >> input;
		try {
			if (0 <= stoi(input) && stoi(input) <= 5) {
				validResponse = true;
				cardsToDiscard = stoi(input);
			}
			else {
				cout << "Please enter a number from 0 to 5" << endl;
			}
		}
		catch (std::invalid_argument& e) {
			// if no conversion could be performed
			cout << "Please enter a numerical answer (0, 1, 2, 3, 4, 5) Error: " << e.what() << endl;
		}
		catch (std::out_of_range& e) {
			// if the converted value would fall out of the range of the result type
			// or if the underlying function (std::strtol or std::strtoull) sets errno
			// to ERANGE.
			cout << "Number is out of range of int capacity. Error: " << e.what() << endl;
		}
	}
	while (cardsToDiscard > 0) {
		cout << "Which card index would you like to discard?" << endl;
		cout << p.hand;
		string discard;
		cin >> discard;
		try {
			Card toDiscard = p.hand[stoi(discard)];
			discardDeck.add_card(toDiscard);
			p.hand.remove_card(stoi(discard));
			cardsToDiscard--;
		}
		catch (std::invalid_argument& e) {
			// if no conversion could be performed
			cout << "Please enter a numerical answer (0, 1, 2, ...). Error: " << e.what() << endl;
		}
		catch (std::out_of_range& e) {
			// if the converted value would fall out of the range of the result type
			// or if the underlying function (std::strtol or std::strtoull) sets errno
			// to ERANGE.
			cout << "Number is out of range of int capacity. Error: " << e.what() << endl;
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
	cout << endl << "Player Name: " << p.name << endl;
	cout << p.hand << endl;
	return success;
}

int FiveCardDraw::before_round() {

	for (int i = 0; i < players.size; ++i) { //New: remove chip from each player before round and add to common chip pot
		--players.at(i)->chips;
		++commonChipPot;
	}

	(this->main_deck).shuffle(); //shuffle main deck
	int start = (this->dealer) + 1;
	int num_players = (this->players).size();
	if ((this->dealer) == num_players - 1) {
		start = 0;
	}
	for (int i = 0; i < 5; ++i) {
		for (size_t j = 0; j < (this->players).size(); ++j) {
			int position = (start + j) % (this->players).size();
			players[position]->hand << (this->main_deck);
		}
	}
	for (size_t j = 0; j < (this->players).size(); ++j) {
		int position = (start + j) % (this->players).size();
		this->before_turn(*players[position]);
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
		int turn_result = this->turn(*players[position]);
		if (turn_result != success) {
			return turn_result;
		}
		int after_turn_result = this->after_turn(*players[position]);
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

	for (size_t i = 0; i < temp_players.size(); i++) {
		if (i == 0) {
			++(temp_players.at(i)->handsWon);
		}
		else {
			++(temp_players[i]->handsLost);
		}
		cout << temp_players.at(i)->name << endl;
		cout << temp_players.at(i)->handsWon << " hands won " << endl;
		cout << temp_players.at(i)->handsLost << " hands lost " << endl;
		cout << "current hand" << endl;
		cout << temp_players.at(i)->hand << endl;
	}

	for (size_t i = 0; i < temp_players.size(); ++i) {
		for (int j = (temp_players.at(i))->hand.size() - 1; j >= 0; --j) {
			Card toMove = (temp_players.at(i)->hand)[j];
			(this->main_deck).add_card(toMove);
			(temp_players.at(i))->hand.remove_card(j);
		}
	}

	main_deck.getCardsFromDeck(discardDeck);
	bool leaveGame = false;

	//NEW. AFTER ROUND CHECK PLAYERS CHIPS AND ASK IF THEY WANT TO RESET OR LEAVE
	for (size_t i = 0; i < temp_players.size(); i++) {
		if (temp_players.at(i)->chips <= 0) {
			cout << "You don't have any chips left. In order to keep playing you must reset your chips to 20. Would you like to do that? Please enter 'yes' or 'no'." << endl;
			string responseChips;
			cin >> responseChips;
			if (responseChips == "yes" || responseChips == "Yes") {
				//reset chips
				temp_players.at(i)->chips = 20;
			}
			else if (responseChips == "no" || responseChips == "No") {
				leaveGame = true;
			}
		}

	}
	while (!leaveGame) {
		cout << "Do any players want to leave the game? Please enter 'yes' or 'no'." << endl;
		string responseLeave;
		cin >> responseLeave;
		if (responseLeave == "yes" || responseLeave == "Yes") {
			cout << "Which player wants to leave? Please enter the name of departing player." << endl;
			string responseName;
			cin >> responseName;
			shared_ptr<Player> player = find_player(responseName);

			if (player) {
				//save player to ofstream
				string fileName = player->name + ".txt";
				ofstream playerFile(fileName, ios::trunc);
				if (playerFile.is_open())
				{
					playerFile << "W" << player->handsWon << "\n";
					playerFile << "L" << player->handsLost << "\n";
					playerFile << "C" << player->chips << "\n"; //new
					playerFile.close();
				}
				remove_player(responseName); //remove player
			}
			else {
				cout << "That player is not currently at the table" << endl;
			}
		}
		else if (responseLeave == "no" || responseLeave == "No") {
			leaveGame = true;
		}
		if (players.size() == 0) {
			break;
		}

	}
	bool joinGame = true;
	while (joinGame) {
		cout << "Do any players want to join the game? Please enter 'yes' or 'no'." << endl;
		string responseJoin;
		cin >> responseJoin;
		if (responseJoin == "no" || responseJoin == "No") {
			joinGame = false;
		}
		else if (responseJoin == "yes" || responseJoin == "Yes") {
			cout << "Which player wants to join? Please enter the name of joining player." << endl;
			string responseNameJoin;
			cin >> responseNameJoin;
			try {
				add_player(responseNameJoin);
			}
			catch (outcome e) {
				if (e == already_playing) {
					cout << "Player already in game. Please enter another response." << endl;
				}
			}
		}
	}
	if (players.size() > 0) {
		dealer = (dealer + 1) % players.size();
	}
	return success;
}
