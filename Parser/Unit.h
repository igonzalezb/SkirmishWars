#pragma once
#include <iostream>
#include <list>
#include <string>

using namespace std;

struct FP
{
	string moon;
	string star;
	string triangle;
	string circle;
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
	string hp;
	string name;
	string path;
	string cost;
	string mp;
	string defence;
	Range range;
	
	FP fpreduced;
	FP fpnormal;
	MovementCost mcost;
public:
	Unit();
	~Unit();
	void setHp(string hp);
	void setPath(string path);
	void setName(string name);
	void setCost(string cost);
	void setMp(string mp);
	void setDefence(string defence);
	void setMinRange(string range);
	void setMaxRange(string range);

	void setFpReducedMoon(string fp);
	void setFpReducedTriangle(string fp);
	void setFpReducedStar(string fp);
	void setFpReducedCircle(string fp);

	void setFpNormalMoon(string fp);
	void setFpNormalTriangle(string fp);
	void setFpNormalStar(string fp);
	void setFpNormalCircle(string fp);

	void setPlainCost(string cost);
	void setRoadCost(string cost);
	void setRiverCost(string cost);
	void setForestCost(string cost);
	void setHillsCost(string cost);

	string getMaxRange();
	string getMinRange();
	string getDefence();
	string getMp();
	string getCost();
	string getHp();
	string getPath();
	string getName();
};