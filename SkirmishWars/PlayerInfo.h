#pragma once
#include <iostream>
#include <string>

using namespace std;

class Player
{
public:
	Player();
	~Player();
	void setMoney(int money);
	int getMoney();
	void setTeam(int team);
	int getTeam();

private:
	string name;
	int money;
	int team;	//TeamNumber
	int ip;

};

