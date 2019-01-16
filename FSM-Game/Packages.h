
#ifndef PACKAGES_H
#define PACKAGES_H

#define DEBUG true

#include <string>
#include <vector>

using namespace std;

typedef char MYBYTE;
typedef enum {
	ACK = 0x01, NAME = 0x10, NAME_IS = 0x11, MAP_IS = 0x12,
	YOU_START = 0x20, I_START = 0x21, PASS = 0x30, MOVE = 0x31,
	PURCHASE = 0x32, ATTACK = 0X33, YOU_WON = 0x40, PLAY_AGAIN = 0x50,
	GAME_OVER = 0x51, ERROR_ = 0xFE, QUIT = 0xFF
}opCodes; //VER ERROR (lo cambie por ERROR_)


class genericPackage
{
public:
	std::vector<char> package;
	virtual void setPackage() = 0;
	opCodes code;
};


class Ack :public genericPackage
{
public:
	Ack() { code = ACK; }
	void setPackage();
};


class Name :public genericPackage
{
public:
	Name() { code = NAME; }
	void setPackage();
};

class NameIs :public genericPackage
{
public:
	NameIs() { code = NAME_IS; }
	void setPackage();
};

class MapIs :public genericPackage
{
public:
	MapIs() { code = MAP_IS; }
	void setPackage();
};

class YouStart :public genericPackage
{
public:
	YouStart() { code = YOU_START; }
	void setPackage();
};

class IStart :public genericPackage
{
public:
	IStart() { code = I_START; }
	void setPackage();
};

class Pass :public genericPackage
{
public:
	Pass() { code = PASS; }
	void setPackage();
};

class Move :public genericPackage
{
public:
	Move() { code = MOVE; }
	void setPackage();
};

class Purchase :public genericPackage
{
public:
	Purchase() { code = PURCHASE; }
	void setPackage();
};

class Attack :public genericPackage
{
public:
	Attack() { code = ATTACK; }
	void setPackage();
};

class YouWon :public genericPackage
{
public:
	YouWon() { code = YOU_WON; }
	void setPackage();
};

class PlayAgain :public genericPackage
{
public:
	PlayAgain() { code = PLAY_AGAIN; }
	void setPackage();
};

class GameOver :public genericPackage
{
public:
	GameOver() { code = GAME_OVER; }
	void setPackage();
};

class Error_ :public genericPackage
{
public:
	Error_() { code = ERROR_; }
	void setPackage();
};

class Quit :public genericPackage
{
public:
	Quit() { code = QUIT; }
	void setPackage();
};


#endif // !PACKAGES_H