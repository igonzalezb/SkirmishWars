#include "Building.h"


Building::Building()
{	
	team = NEUTRO;	
}

//Building::Building(string cp, string name, string path, string type, string team)
Building::Building(int cp, string name, string path, string type, string team)
{
	
	this->cp = cp;
	this->name = name;
	this->type = type;

	this->team = TeamNumber(stoi(team));



	char temp[50];
	sprintf(temp, path.c_str(), this->team);
	this->path = temp;
}

Building::~Building()
{
}

void Building::setName(string name)
{
	this->name = name;
}

void Building::setCp(int cp)
{
	this->cp = cp;
}

void Building::setPath(string path)
{
	this->path = path;
	/*char temp[50];
	sprintf(temp, path.c_str(),  this->team);
	this->path = temp;*/
}

string Building::getPath()
{
	return path;
}

int Building::getCp()
{
	return cp;
}

string Building::getName()
{
	return name;
}

void Building::setTeam(TeamNumber team)
{
	/*if(type.size() > 2)
		type += to_string(team);	*/		//PROBAR!!!!
	this->team = team;
}

void Building::updatePath()
{
	int pos;
	if ((pos = path.find('0')) != string::npos)
	{
		path.erase(pos, 1);
		path.insert(pos, to_string(team));
	}
	if ((pos = path.find('1')) != string::npos)
	{
		path.erase(pos, 1);
		path.insert(pos, to_string(team));
	}
	if ((pos = path.find('2')) != string::npos)
	{
		path.erase(pos, 1);
		path.insert(pos, to_string(team));
	}


}

TeamNumber Building::getTeam()
{
	return team;
}

TeamColor Building::getTeamColor()
{
	return teamColor;
}

void Building::setTeamColor(TeamColor teamco_)
{
	this->teamColor = teamco_;
}

string Building::getType()
{
	return type;
}

void Building::setType(string type)
{
	this->type = type;
}

void Building::removeFog()
{
	fogOfWar = false;
}