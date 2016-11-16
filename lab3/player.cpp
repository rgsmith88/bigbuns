#include "stdafx.h"
#include "functions.h"
#include "deck.h"
#include "hand.h"
#include "player.h"
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>

player::player(std::string n) {
	name = n;
	handsWon = 0;
	handsLost = 0;
	string fileName = n + ".txt";

	string line;
	ifstream ifs(fileName);
	bool wExtracted = false;
	bool lExtracted = false;


	if (ifs.is_open())
	{
		while (getline(ifs, line))
		{
			for (unsigned int i = 0; i <= line.length(); i++)
			{
				char p = line.at(i);
				if (p == 'W')
				{
					handsWon = line.at(i + 1);
					wExtracted = true;

				}
				else if (p == 'L')
				{
					handsLost = line.at(i + 1);
				}
			}
		}
		if (!wExtracted || !lExtracted)
		{
			handsWon = 0;
			handsLost = 0;
		}

	}
}
ostream& operator<< (ostream& out, const player& p){
	out << p.name << " games won: " << p.handsWon << " games_lost " << p.handsLost;
	return out;
	}

