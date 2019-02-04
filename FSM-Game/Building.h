#pragma once
#include <iostream>
#include <list>
#include <string>

using namespace std;

typedef enum { WHITE, RED, BLUE, YELLOW, GREEEN } TeamColor;
typedef enum {NEUTRO, EQUIPO1, EQUIPO2}TeamNumber;

class Building
{
private:
	int cp;
	string name;
	string path;
	string type;
	TeamNumber team;
	TeamColor teamColor;
	bool fogOfWar;

public:
	Building();
	Building(int cp, string name, string path, string type, string team);
	~Building();
	void setCp(int cp);
	void setPath(string path);
	void setName(string name);
	int getCp();
	string getPath();
	string getName();
	void setTeam(TeamNumber team);
	TeamNumber getTeam();
	TeamColor getTeamColor();
	void setTeamColor(TeamColor teamco_);
	string getType();
	void setType(string type);
	void removeFog();
	void updatePath();
};