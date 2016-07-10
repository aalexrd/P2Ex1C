#pragma once
#ifndef Player_H
#define Player_H
#include <string>
using namespace std;

class Player
{
private:
	string name;
	int points;
public:
	Player();
	Player(string name, int points);
	void setName(string name);
	void setPoints(int points);
	string getName() const;
	int getPoints() const;
};
#endif
