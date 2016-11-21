#include "stdafx.h"
#include "functions.h"
#include "deck.h"
#include "hand.h"
#include "game.h"
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>

using namespace std;

int main(int argc, char* argv[]) {

	if (argc < 4) { //program needs at least 3 inputs
		const char* message = "Please pass the name of a game followed by the names of two or more players";
		int usageError = usageMessage(argv[0], message); // program should call the usage message function
		return too_few_arguments; // return the value returned from that call
	}

	const char* program_name = argv[0];
	const char* game_name = argv[1];

	Game *myGame;
	try {
		myGame -> start_game(game_name);
	}
	catch (int e) {
		if (e == game_already_started) {
			cout << "The game has already started" << endl;
		}
		if (e == unknown_game) {
			cout << "The game you have entered is unknown, please enter FiveCardDraw" << endl;
		}
		myGame -> stop_game();
		return e;
	}
	shared_ptr<Game> myGame_instance;

	try {
		myGame_instance = myGame -> instance();
	}
	catch (int e) {
		cout << "The instance is not available" << endl;
		myGame_instance-> stop_game();
		return e;
	}

	int number_of_players = argc - 2;
	for (int i = 0; i < number_of_players; ++i) {
		try {
			myGame_instance->add_player(argv[i + 2]);
		}
		catch (int e) {
			cout << argv[i + 2] << " is already playing this game" << endl;
			return e;
		}
	}

	while (myGame_instance -> size() >= 2) { //at least two palyers in the game
		myGame_instance-> before_round();
		myGame_instance-> round();
		myGame_instance-> after_round();
	}

	if (myGame_instance->size() == 0) {
		myGame_instance-> stop_game();
		return 0;
	}
}