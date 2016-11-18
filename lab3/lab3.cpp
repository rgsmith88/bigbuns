#include "stdafx.h"
#include "functions.h"
#include "deck.h"
#include "hand.h"
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>

using namespace std;

int main(int argc, char* argv[]) {
	
	if (argc < 4){ //program needs at least 3 inputs
		const char* message = "Please pass the name of a game followed by the names of two or more players";
		int usageError = usageMessage(argv[0], message); // program should call the usage message function
		return too_few_arguments; // return the value returned from that call
	}
	
	start_game(argv[1]);
		
	instance();
	
	while (players.size() >= 2){ //at least two palyers in the game
		before_round();
		round();
		after_round();
	}
	
	if (players.size() == 0){
		stop_game();
		return 0;
	}
	
	
	/*
	if (argc == 1) { // program should first check that exactly one argument has been passed to it
		const char* message = "In order to use the program type in two or three arguments when using the method with the correct syntax";
		int usageError = usageMessage(argv[0], message); // program should call the usage message function
		return no_arguments; // return the value returned from that call
	}
	else if (argc == 2 && strcmp(argv[1], "-shuffle") == 0) {
		const char* message = "In order to use the program please insert another argument for a filename";
		int usageError = usageMessage(argv[0], message); // program should call the usage message function
		return just_shuffle; // return the value returned from that call
	}
	else if (argc == 3 && strcmp(argv[1], "-shuffle") != 0 && strcmp(argv[2], "-shuffle") != 0) {
		const char* message = "In order to use the program please insert '-shuffle' as an argument instead of one of the present arguments";
		int usageError = usageMessage(argv[0], message); // program should call the usage message function
		return need_shuffle; // return the value returned from that call
	}
	else if (argc > 3) {
		const char* message = "In order to use the program please only use at most two command line arguments";
		int usageError = usageMessage(argv[0], message); // program should call the usage message function
		return too_many_arguments; // return the value returned from that call
	}
	else if (argc < 0) { // program should first check that exactly one argument has been passed to it
		const char* message = "In order to use the program type in two or three arguments when using the method with the correct syntax";
		int usageError = usageMessage(argv[0], message); // program should call the usage message function
		return usageError; // return the value returned from that call
	}

	char* filename = "";
	bool shuffle = false;
	if (argc == 2) {
		filename = argv[1];
	}
	else if (argc == 3 && strcmp(argv[1], "-shuffle") == 0) {
		filename = argv[2];
		shuffle = true;
	}
	else if (argc == 3 && strcmp(argv[2], "-shuffle") == 0) {
		filename = argv[1];
		shuffle = true;
	}
	Deck deck = Deck(filename);
	if (shuffle) {
		deck.shuffle();
	}
	vector<Hand> hands;
	for (int i = 0; i < 9; ++i) {
		Hand tempHand = Hand();
		hands.push_back(tempHand);
	}
	for (int i = 0; i < 5; ++i) {
		for (int j = 0; j < 9; ++j) {
			Hand tempHand = hands.at(j);
			tempHand << deck;
			hands.at(j) = tempHand;
		}
	}
	cout << deck << endl;
	for (Hand h : hands) {
		cout << h;
	}
	sort(hands.begin(), hands.end());
	for (Hand h : hands) {
		cout << h;
	}
	sort(hands.begin(), hands.end(), poker_rank);
	for (Hand h : hands) {
		cout << h;
	}

	return success;
	*/
}
