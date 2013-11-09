/*
 * main.cpp
 *
 *  Created on: 09/11/2013
 *      Author: Windsdon
 */

#include <iostream>
#include "Game.h"

using namespace std;


int main(int argc, char **argv) {
	cout << "GunMan, build " << __DATE__ << " - " << __TIME__ << endl;

	Game game;
	game.onStart();

	cout << "Ended." << endl;
	return 0;
}

