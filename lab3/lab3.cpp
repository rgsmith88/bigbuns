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

	Game myGame;
	try {
		myGame.start_game(game_name);
	}
	catch (int e) {
		if (e == game_already_started) {
			cout << "The game has already started" << endl;
		}
		if (e == unknown_game) {
			cout << "The game you have entered is unknown, please enter FiveCardDraw" << endl;
		}
		myGame.stop_game();
		return e;
	}

	try {
		shared_ptr<Game> myGame_instance = myGame.instance();
	}
	catch (int e) {
		cout << "The instance is not available" << endl;
		myGame.stop_game();
		return e;
	}

	while (myGame.players.size() >= 2) { //at least two palyers in the game
		myGame.before_round();
		myGame.round();
		myGame.after_round();
	}

	if (players.size() == 0) {
		myGame.stop_game();
		return 0;
	}
}