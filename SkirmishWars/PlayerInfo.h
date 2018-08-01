#pragma once
#include <iostream>


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
	int money;
	int team;	//TeamNumber

};

