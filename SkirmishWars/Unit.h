#pragma once

#include "Map.h"

//----- UNIT TYPE [CODES] -----
#define INFANTRIES	"in"#x
#define MECHS		"me"#x
#define ROCKETS		"ro"#x
#define RECONS		"re"#x
#define APCS		"ap"#x
#define ANTIAIR		"aa"#x
#define ARTILLERY	"ar"#x
#define TANKS		"ta"#x
#define MEDTANKS	"mt"#x

class Unit
{
public:
	Unit();
	~Unit();
	//Attack Unit
	//Attack Building
	//Move
	//Defend

private:
	TeamColor team;
	int health;
	int attackDamage;
};