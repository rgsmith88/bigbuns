#include "stdafx.h"
#include "deck.h"
#include "functions.h"
#include "games.h"
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

shared_ptr<GameBase> Game::ptr; //is this singular?

static shared_ptr<Game> Game::instance() {
	if (!ptr) {
		throw instance_not_available;
	}
	shared_ptr<Game> ptr_copy(ptr);
	return ptr_copy;
}

static void Game::start_game(const string& str) {
	if (ptr) {
		throw game_already_started;
	}
	else if (str.find("FiveCardDraw") < 0) { //should this be else if?
		throw unknown_game;
	}
	else {
		ptr = static_pointer_cast<Game>(make_shared<FiveCardDraw>());
	}
}

static void Game::stop_game() {
	if (!ptr) {
		throw no_game_in_progress;
	}
	ptr.reset();
}

shared_ptr<Player> Game::find_player(const string& str) {
	for (shared_ptr<Player> p : players) {
		if ((*p) -> name == str) {
			return *p;
		}
	}
	shared_ptr<Player> not_found;
	return not_found;

}

void Game::add_player(const string& str) {
	shared_ptr<Player> player_found = find_player(str);
	if (player_found) {
		throw already_playing;
	}
	else {
		players.push_back(make_shared<Player>(str));
	}
}

void Game::remove_player(const string& str) {
	for (shared_ptr<Player> p : players) {
		if ((*p)->name == str) {
			players.erase(p);
			return;
		}
	}
}
