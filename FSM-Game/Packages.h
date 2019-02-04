
#ifndef PACKAGES_H
#define PACKAGES_H

#define DEBUG true

#include <string>
#include <vector>
#include "Game.h"

using namespace std;

typedef char MYBYTE;

typedef enum {
	OP_ACK = 0x01, OP_NAME = 0x10, OP_NAME_IS = 0x11, OP_MAP_IS = 0x12,
	OP_YOU_START = 0x20, OP_I_START = 0x21, OP_PASS = 0x30, OP_MOVE = 0x31,
	OP_PURCHASE = 0x32, OP_ATTACK = 0X33, OP_YOU_WON = 0x40, OP_PLAY_AGAIN = 0x50,
	OP_GAME_OVER = 0x51, OP_ERROR = 0xFE, OP_QUIT = 0xFF
}opCodes; 

class genericPackage
{
public:
	genericPackage();
	~genericPackage();
	//genericPackage(Game* gameInfo);
	std::vector<char> package;
	virtual void setPackage() = 0;
	opCodes code;
	//Game* gameInfo;
};


class Ack :public genericPackage
{
public:
	Ack() { code = OP_ACK; }
	void setPackage();
};


class Name :public genericPackage
{
public:
	Name() { code = OP_NAME; }
	void setPackage();
};

class NameIs :public genericPackage
{
private:
	string nameIs;
public:
	NameIs(string nameIs);
	void setPackage();
};

class MapIs :public genericPackage
{
private:
	string mapName;
	char checksum;
public:
	MapIs(string mapName, char checksum);
	void setPackage();
};

class YouStart :public genericPackage
{
public:
	YouStart() { code = OP_YOU_START; }
	void setPackage();
};

class IStart :public genericPackage
{
public:
	IStart() { code = OP_I_START; }
	void setPackage();
};

class Pass :public genericPackage
{
public:
	Pass() { code = OP_PASS; }
	void setPackage();
};

class Move :public genericPackage
{
private:
	int attacker_i;
	int attacker_j;
	int defender_i;
	int defender_j;
public:
	Move(int attacker_i, int attacker_j, int defender_i, int defender_j);
	void setPackage();
};

class Purchase :public genericPackage
{

private:
	string unit;
	int defender_i;
	int defender_j;
public:
	Purchase(string typeOfUnit, int defender_i, int defender_j);
	void setPackage();
};

class Attack :public genericPackage
{
private:
	int attacker_i;
	int attacker_j;
	int defender_i;
	int defender_j;
	int dado;
public:
	Attack(int attacker_i, int attacker_j, int defender_i, int defender_j, int dado);
	void setPackage();
};

class YouWon :public genericPackage
{
public:
	YouWon() { code = OP_YOU_WON; }
	void setPackage();
};

class PlayAgain :public genericPackage
{
public:
	PlayAgain() { code = OP_PLAY_AGAIN; }
	void setPackage();
};

class GameOver :public genericPackage
{
public:
	GameOver() { code = OP_GAME_OVER; }
	void setPackage();
};

class Error_ :public genericPackage
{
public:
	Error_() { code = OP_ERROR; }
	void setPackage();
};

class Quit :public genericPackage
{
public:
	Quit() { code = OP_QUIT; }
	void setPackage();
};




#endif // !PACKAGES_H