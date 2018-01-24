#include "Unit.h"

Unit::Unit()
{
}

Unit::~Unit()
{
}

void Unit::setHp(string hp)
{
	this->hp = hp;
}

void Unit::setPath(string path)
{
	this->path = path;
}

void Unit::setName(string name)
{
	this->name = name;
}

void Unit::setCost(string cost)
{
	this->cost = cost;
}

void Unit::setMp(string mp)
{
	this->mp = mp;
}

void Unit::setdefense(string defense)
{
	this->defense = defense;
}

void Unit::setMinRange(string range)
{
	this->range.min = range;
}

void Unit::setMaxRange(string range)
{
	this->range.max = range;
}

void Unit::setFpReducedMoon(string fp)
{
	this->fpreduced.moon = fp;
}

void Unit::setFpReducedTriangle(string fp)
{
	this->fpreduced.triangle = fp;
}

void Unit::setFpReducedStar(string fp)
{
	this->fpreduced.star = fp;
}

void Unit::setFpReducedCircle(string fp)
{
	this->fpreduced.circle = fp;
}

void Unit::setFpReducedSquare(string fp)
{
	this->fpreduced.square = fp;
}

void Unit::setFpNormalMoon(string fp)
{
	this->fpnormal.moon = fp;
}

void Unit::setFpNormalTriangle(string fp)
{
	this->fpnormal.triangle = fp;
}

void Unit::setFpNormalStar(string fp)
{
	this->fpnormal.star = fp;
}

void Unit::setFpNormalCircle(string fp)
{
	this->fpnormal.circle = fp;
}

void Unit::setFpNormalSquare(string fp)
{
	this->fpnormal.square = fp;
}

void Unit::setPlainCost(string cost)
{
	this->mcost.plain = cost;
}

void Unit::setRoadCost(string cost)
{
	this->mcost.road = cost;
}

void Unit::setRiverCost(string cost)
{
	this->mcost.river = cost;
}

void Unit::setForestCost(string cost)
{
	this->mcost.forest = cost;
}

void Unit::setHillsCost(string cost)
{
	this->mcost.hills = cost;
}

string Unit::getMaxRange()
{
	return range.max;
}

string Unit::getMinRange()
{
	return range.min;
}

string Unit::getdefense()
{
	return defense;
}

string Unit::getMp()
{
	return mp;
}

string Unit::getCost()
{
	return cost;
}

string Unit::getHp()
{
	return hp;
}

string Unit::getPath()
{
	return path;
}

string Unit::getName()
{
	return name;
}
