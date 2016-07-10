#pragma once
#ifndef Juego_H
#define Juego_H
#include <iostream>
#include <fstream>
#include "Player.h"
using namespace std;

class Game
{
private:
	Player player1;
	Player player2;
	string word;
	string input;
public:
	Game();
	~Game();
	Game(Player player1, Player player2, char* word, char* input);
	bool letterInput();
	static void setw(string i, int q = 0);
	void UI();
	void print(int i);
	bool isWinner() const;
	void save(Player jug) const;
	static bool option();
	static string readString();
};
#endif
