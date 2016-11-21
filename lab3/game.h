#ifndef game_h
#define game_h
#include "stdafx.h"
#include "functions.h"
#include "deck.h"
#include <string>
#include <vector>
#include <iostream>
#include <memory>

using namespace std;

class Deck;

class Game {
	protected:
		static shared_ptr<Game> ptr;
		Deck main_deck;
		vector<shared_ptr<Player>> players;
	public:
		static shared_ptr<Game> instance();
		static void start_game(const string& str);
		static void stop_game();
		void add_player(const string& str); //change return type?
		shared_ptr<Player> find_player(const string& str);
		//Don't need to include virtual destructor b/c of shared_ptrs
		virtual int before_turn (Player& player) = 0;
		virtual int turn(Player& player) = 0;
		virtual int after_turn(Player& player) = 0;
		virtual int before_round() = 0;
		virtual int round() = 0;
		virtual int after_round() = 0;
		void remove_player(const string& str);
	
};

#endif;
