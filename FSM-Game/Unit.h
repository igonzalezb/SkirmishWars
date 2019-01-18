#pragma once
#include <iostream>
#include <list>
#include <string>

using namespace std;

#include "Building.h"
//typedef enum { WHITE, RED, BLUE, YELLOW, GREEEN } TeamColor;

struct FP
{
	string moon;
	string star;
	string triangle;
	string circle;
	string square;
};

struct Range
{
	string min;
	string max;
};

struct MovementCost
{
	string plain;
	string road;
	string forest;
	string river;
	string hills;
};

class Unit
{
private:
	//string hp;
	int hp;
	string name;
	string path;
	string cost;
	string mp;
	string defense;
	string symbol;
	Range range;
	string type;
	FP fpreduced;
	FP fpnormal;
	MovementCost mcost;
	TeamNumber team;
	TeamColor teamColor;




	bool fogOfWar;
public:
	Unit();
	Unit(list<Unit>::iterator it);
	~Unit();

	void setHp(int hp);
	void setPath(string path);
	void setName(string name);
	void setCost(string cost);
	void setMp(string mp);
	void setdefense(string defense);


	void setMinRange(string range);
	void setMaxRange(string range);
	void setType(string type);
	void setTeam(TeamNumber team);
	void setSymbol(string symbol);
	void setFpReducedMoon(string fp);
	void setFpReducedTriangle(string fp);
	void setFpReducedStar(string fp);
	void setFpReducedCircle(string fp);
	void setFpReducedSquare(string fp);

	void setFpNormalMoon(string fp);
	void setFpNormalTriangle(string fp);
	void setFpNormalStar(string fp);
	void setFpNormalCircle(string fp);
	void setFpNormalSquare(string fp);

	void setPlainCost(string cost);
	void setRoadCost(string cost);
	void setRiverCost(string cost);
	void setForestCost(string cost);
	void setHillsCost(string cost);

	Range getRange();
	string getdefense();
	string getMp();
	string getCost();
	int getHp();
	string getPath();
	string getName();
	TeamColor getTeam();
	string getSymbol();
	string getType();
	FP getFpReduced();
	FP getFpNormal();
	MovementCost getMc();
	void removeFog();
};